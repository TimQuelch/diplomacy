#include "utils.h"

#include <fstream>
#include <stdexcept>

#include <fmt/format.h>

namespace diplomacy::utils {
    [[nodiscard]] auto loadJson(std::filesystem::path const& jsonPath) -> nlohmann::json {
        if (std::filesystem::exists(jsonPath)) {
            auto stream = std::ifstream{jsonPath};
            auto json = nlohmann::json{};
            stream >> json;
            return json;
        } else {
            throw std::runtime_error{
                fmt::format("Requested file does not exist: {}", jsonPath.string())};
        }
    }
} // namespace diplomacy
