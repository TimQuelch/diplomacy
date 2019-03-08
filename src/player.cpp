#include "player.h"

#include "map.h"

namespace diplomacy {
    Player::Player(nlohmann::json const& playerConfig, Map const& map)
        : name_{"Player name"}, empireName_{playerConfig["empire"]} {
        for (auto region : playerConfig["regions"]) {
            regions_.push_back(&(map.findFromAbbr(region)));
        }
        for (auto region : playerConfig["armies"]) {
            units_.push_back(Unit{Unit::Type::army, this, &(map.findFromAbbr(region))});
        }
        for (auto region : playerConfig["fleets"]) {
            units_.push_back(Unit{Unit::Type::fleet, this, &(map.findFromAbbr(region))});
        }
    }
} // namespace diplomacy
