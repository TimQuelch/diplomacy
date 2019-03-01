#include "game.h"

#include "map.h"
#include "player.h"
#include "region.h"
#include "unit.h"
#include "utils.h"

namespace diplomacy {
    Game::Game(std::filesystem::path const& configPath)
        : map_{std::make_unique<Map>(utils::loadJson(configPath))} {}
} // namespace diplomacy
