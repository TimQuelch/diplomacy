#include "map.h"

#include <fstream>

#include <nlohmann/json.hpp>

namespace diplomacy {
    void loadMap(std::filesystem::path const& mapJson) {
        auto const json = [&mapJson]() {
            auto stream = std::ifstream{mapJson};
            auto json = nlohmann::json{};
            stream >> json;
            return json;
        }();
    }
} // namespace diplomacy
