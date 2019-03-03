#pragma once

#include <filesystem>

#include "map.h"
#include "player.h"

namespace diplomacy {
    class Game {
    public:
        Game() = delete;
        Game(Game const&) = delete;
        Game& operator=(Game const&) = delete;

        Game(Game&&) = default;
        Game& operator=(Game&&) = default;

        Game(std::filesystem::path const& configPath);

    private:
        std::unique_ptr<Map> map_;
        std::vector<std::unique_ptr<Player>> players_;
    };

    static_assert(!std::is_default_constructible_v<Game>);
    static_assert(!std::is_copy_constructible_v<Game>);
    static_assert(!std::is_copy_assignable_v<Game>);

    static_assert(std::is_nothrow_move_constructible_v<Game>);
    static_assert(std::is_nothrow_move_assignable_v<Game>);
    static_assert(std::is_nothrow_destructible_v<Game>);
    static_assert(std::is_nothrow_swappable_v<Game>);
} // namespace diplomacy
