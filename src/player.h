#pragma once

#include <string>
#include <string_view>
#include <vector>

#include "unit.h"

namespace diplomacy {
    class Player {
    public:
        Player() = delete;
        Player(std::string_view name, std::string_view empireName) noexcept
            : name_{name}, empireName_{empireName} {}

        [[nodiscard]] auto name() const noexcept { return name_; }
        [[nodiscard]] auto empireName() const noexcept { return empireName_; }

        void addUnit(Unit::Type type, Region* region) noexcept {
            units_.push_back(Unit{type, this, region});
        };

    private:
        std::string name_ = {};
        std::string empireName_ = {};
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