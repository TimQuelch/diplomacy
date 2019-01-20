#include "map.h"

#include "region.h"
#include "utils.h"

#include <cassert>
#include <iostream>
#include <stdexcept>

#include <fmt/format.h>
#include <fmt/ranges.h>

namespace diplomacy {
    namespace {
        constexpr auto requiredMembers = std::array{"abbr", "name", "type", "borders"};

        [[nodiscard]] auto findDuplicateAbbrs(nlohmann::json const& json) noexcept {
            auto abbrs = std::vector<std::string>{};
            abbrs.reserve(json.size());

            std::transform(
                json.cbegin(), json.cend(), std::back_inserter(abbrs), [](auto const& region) {
                    auto a = std::string{region["abbr"]};
                    std::transform(a.begin(), a.end(), a.begin(), [](unsigned char c) {
                        return std::tolower(c);
                    });
                    return a;
                });

            std::sort(abbrs.begin(), abbrs.end());
            auto uniqueAbbrs = std::vector<std::string>{};
            std::unique_copy(abbrs.begin(), abbrs.end(), std::back_inserter(uniqueAbbrs));
            auto duplicates = std::vector<std::string>{};
            std::set_difference(abbrs.begin(),
                                abbrs.end(),
                                uniqueAbbrs.begin(),
                                uniqueAbbrs.end(),
                                std::back_inserter(duplicates));
            return duplicates;
        }

        [[nodiscard]] auto findMissingFields(nlohmann::json const& json) noexcept {
            auto missing = std::vector<std::pair<std::string, std::vector<std::string>>>{};
            for (auto const& region : json) {
                auto membersMissing = std::vector<std::string>{};
                std::copy_if(requiredMembers.begin(),
                             requiredMembers.end(),
                             std::back_inserter(membersMissing),
                             [&region](auto const& mem) { return region.count(mem) == 0; });
                if (!membersMissing.empty()) {
                    missing.push_back({region["abbr"], membersMissing});
                }
            }
            return missing;
        }

        [[nodiscard]] auto findMissingBorders(nlohmann::json const& json) noexcept {
            auto missingBorders = std::vector<std::pair<std::string, std::vector<std::string>>>{};
            for (auto const& region : json) {
                auto regionMissingBorders = std::vector<std::string>{};
                for (std::string bordering : region["borders"]) {
                    if (std::find_if(json.cbegin(), json.cend(), [&bordering](auto const& other) {
                            return other["abbr"] == bordering;
                        }) == json.cend()) {
                        regionMissingBorders.push_back(bordering);
                    }
                }
                if (!regionMissingBorders.empty()) {
                    missingBorders.push_back({region["abbr"], regionMissingBorders});
                }
            }
            return missingBorders;
        }

        [[nodiscard]] auto findNonReciprocalBorders(nlohmann::json const& json) noexcept {
            auto nonReciprocated = std::vector<std::pair<std::string, std::vector<std::string>>>{};
            for (auto const& region : json) {
                auto regionNonReciprocated = std::vector<std::string>{};
                for (std::string bordering : region["borders"]) {
                    if (json.count(bordering) > 0) {
                        auto const& other = json[bordering]["borders"];
                        if (std::find(other.begin(), other.end(), region["abbr"]) == other.end()) {
                            regionNonReciprocated.push_back(bordering);
                        }
                    }
                }
                if (!regionNonReciprocated.empty()) {
                    nonReciprocated.push_back({region["abbr"], regionNonReciprocated});
                }
            }
            return nonReciprocated;
        }

        [[nodiscard]] auto verifyJsonStructure(nlohmann::json const& json) noexcept {
            auto errorString = std::string{};

            // Ensure abbreviations are unique
            if (auto const duplicates = findDuplicateAbbrs(json); !duplicates.empty()) {
                errorString += fmt::format("Duplicate regions present: {}.\n", duplicates);
            }

            // Ensure all required fields are present
            if (auto missing = findMissingFields(json); !missing.empty()) {
                for (auto const& region : missing) {
                    errorString +=
                        fmt::format("Missing fields in {}: {}.\n", region.first, region.second);
                }
            }

            // Ensure all stated borders exist
            if (auto missingBorders = findMissingBorders(json); !missingBorders.empty()) {
                for (auto const& region : missingBorders) {
                    errorString += fmt::format(
                        "Border(s) stated in {} don't exist: {}.\n", region.first, region.second);
                }
            }

            // Ensure all borders are reciprcated
            if (auto nonReciprocated = findNonReciprocalBorders(json); !nonReciprocated.empty()) {
                for (auto const& region : nonReciprocated) {
                    errorString += fmt::format("Border(s) stated in {} are not reciprocated: {}.\n",
                                               region.first,
                                               region.second);
                }
            }

            auto ret = std::optional<std::string>{};
            if (errorString != "") {
                ret = errorString;
            }
            return ret;
        }

        [[nodiscard]] constexpr auto jsonToRegionType(std::string_view type) noexcept {
            if (type == "land") {
                return Region::Type::land;
            } else if (type == "sea") {
                return Region::Type::sea;
            }
            assert(!"Invalid region type");
        }
    } // namespace

    Map::Map(nlohmann::json const& config) {
        auto const& regionsJson = config["regions"];
        auto const& scsJson = config["SCs"];

        if (auto ret = verifyJsonStructure(regionsJson)) {
            throw std::runtime_error{*ret};
        }

        assert(regions_.empty());

        // Create regions
        std::transform(regionsJson.begin(),
                       regionsJson.end(),
                       std::back_inserter(regions_),
                       [](auto const& region) {
                           return std::make_unique<Region>(region["name"],
                                                           region["abbr"],
                                                           false,
                                                           jsonToRegionType(region["type"]));
                       });

        // Assign borders
        for (auto const& regionJson : regionsJson) {
            auto const current =
                std::find_if(regions_.cbegin(), regions_.cend(), [&regionJson](auto const& region) {
                    return region->abbr() == regionJson["abbr"];
                });
            for (std::string border : regionJson["borders"]) {
                auto const other =
                    std::find_if(regions_.cbegin(), regions_.cend(), [&border](auto const& region) {
                        return region->abbr() == border;
                    });
                borders_.insert({current->get(), other->get()});
            }
        }

        // Transform regions to coasts
        for (auto const& region : regions_) {
            if (region->type() == Region::Type::sea) {
                auto const [b, e] = borders_.equal_range(region.get());
                std::for_each(b, e, [](auto const& r) {
                    if (r.second->type() == Region::Type::land) {
                        r.second->setType(Region::Type::coast);
                    }
                });
            }
        }

        // Transform to SCs
        for (std::string abbr : scsJson) {
            auto const region =
                std::find_if(regions_.cbegin(), regions_.cend(), [&abbr](auto const& region) {
                    return region->abbr() == abbr;
                });
            if (region == regions_.end()) {
                throw std::runtime_error{fmt::format("Setting missing region, '{}', as SC", abbr)};
            }
            (**region).setSc(true);
        }
    }
} // namespace diplomacy
