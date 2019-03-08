#pragma once

#include <string>
#include <string_view>
#include <vector>

#include <nlohmann/json.hpp>

#include "unit.h"

namespace diplomacy {
    class Map;

    class Player {
    public:
        Player() = delete;
        Player(nlohmann::json const& playerConfig, Map const& map);

        [[nodiscard]] auto name() const noexcept { return name_; }
        [[nodiscard]] auto empireName() const noexcept { return empireName_; }

    private:
        std::string name_ = {};
        std::string empireName_ = {};
        std::vector<Region const*> regions_ = {};
        std::vector<Unit> units_ = {};
    };

    static_assert(!std::is_default_constructible_v<Player>);

    static_assert(std::is_copy_constructible_v<Player>);
    static_assert(std::is_copy_assignable_v<Player>);
    static_assert(std::is_nothrow_move_constructible_v<Player>);
    static_assert(std::is_nothrow_move_assignable_v<Player>);
    static_assert(std::is_nothrow_destructible_v<Player>);
    static_assert(std::is_nothrow_swappable_v<Player>);
} // namespace diplomacy
