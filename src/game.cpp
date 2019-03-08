#include "game.h"

#include "region.h"
#include "unit.h"
#include "utils.h"

namespace diplomacy {
    Game::Game(std::filesystem::path const& configPath) {
        auto const config = utils::loadJson(configPath);

        map_ = std::make_unique<Map>(config);

        std::transform(config["players"].cbegin(),
                       config["players"].cend(),
                       std::back_inserter(players_),
                       [this](auto const& playerConfig) {
                           return std::make_unique<Player>(playerConfig, *map_);
                       });
    }
} // namespace diplomacy
