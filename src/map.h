#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include <nlohmann/json.hpp>

#include "region.h"

namespace diplomacy {
    class Map {
    public:
        Map() = delete;
        Map(Map const&) = delete;
        Map& operator=(Map const&) = delete;

        Map(Map&&) = default;
        Map& operator=(Map&&) = default;

        Map(nlohmann::json const& config);

        [[nodiscard]] unsigned totalScs() const noexcept { return totalScs_; }

        [[nodiscard]] Region& findFromAbbr(std::string_view abbr);
        [[nodiscard]] Region const& findFromAbbr(std::string_view abbr) const;

    private:
        std::vector<std::unique_ptr<Region>> regions_ = {};
        std::unordered_multimap<Region*, Region*> borders_ = {};

        unsigned totalScs_ = {};
    };

    static_assert(!std::is_default_constructible_v<Map>);
    static_assert(!std::is_copy_constructible_v<Map>);
    static_assert(!std::is_copy_assignable_v<Map>);

    static_assert(std::is_nothrow_move_constructible_v<Map>);
    static_assert(std::is_nothrow_move_assignable_v<Map>);
    static_assert(std::is_nothrow_destructible_v<Map>);
    static_assert(std::is_nothrow_swappable_v<Map>);
} // namespace diplomacy
