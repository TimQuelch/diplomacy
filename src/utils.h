#pragma once

#include <filesystem>

#include <nlohmann/json.hpp>

namespace diplomacy::utils {
    [[nodiscard]] auto loadJson(std::filesystem::path const& jsonPath) -> nlohmann::json;
}
