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
                       [this](auto const& player) {
                           auto p = Player{"Player name", player["empire"]};
                           for (auto region : player["armies"]) {
                               p.addUnit(Unit::Type::army, &(map_->findFromAbbr(region)));
                           }
                           for (auto region : player["fleets"]) {
                               p.addUnit(Unit::Type::fleet, &(map_->findFromAbbr(region)));
                           }
                           return std::make_unique<Player>(p);
                       });
    }
} // namespace diplomacy
