#pragma once

#include <stdexcept>
#include <type_traits>

#include <fmt/format.h>

namespace diplomacy {
    class Player;
    class Region;

    class Unit {
    public:
        enum class Type { army, fleet };

        Unit() = delete;
        constexpr Unit(Type type, Player* player, Region* region) noexcept
            : type_{type}, player_{player}, region_{region} {}

        [[nodiscard]] constexpr auto type() const noexcept { return type_; }

        [[nodiscard]] constexpr auto const& player() const noexcept { return *player_; }
        [[nodiscard]] constexpr auto& player() noexcept { return *player_; }

        [[nodiscard]] constexpr auto const& region() const { return *region_; }
        [[nodiscard]] constexpr auto& region() noexcept { return *region_; }

    private:
        Type type_ = Type::army;
        Player* player_;
        Region* region_;
    };

    static_assert(!std::is_default_constructible_v<Unit>);
    static_assert(std::is_copy_constructible_v<Unit>);

    static_assert(std::is_nothrow_move_constructible_v<Unit>);
    static_assert(std::is_nothrow_destructible_v<Unit>);
    static_assert(std::is_nothrow_swappable_v<Unit>);

    static_assert(std::is_trivially_copy_constructible_v<Unit>);
    static_assert(std::is_trivially_move_constructible_v<Unit>);
    static_assert(std::is_trivially_destructible_v<Unit>);
} // namespace diplomacy
