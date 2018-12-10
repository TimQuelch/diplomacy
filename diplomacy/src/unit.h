#pragma once

#include "region.h"

#include <stdexcept>
#include <type_traits>

#include <fmt/format.h>

namespace diplomacy {
    class Unit {
    public:
        enum class Type { army, fleet };

        constexpr Unit() noexcept = default;
        constexpr Unit(Type type, Region* region) noexcept : type_{type}, region_{region} {}

        [[nodiscard]] constexpr auto type() const noexcept { return type_; }
        [[nodiscard]] auto region() const {
            if (!region_) {
                throw std::runtime_error{"Dereferencing Region pointer which is null"};
            }
            return *region_;
        }

    private:
        Type type_ = Type::army;
        Region* region_ = nullptr;
    };

    static_assert(std::is_copy_constructible_v<Unit>);

    static_assert(std::is_nothrow_default_constructible_v<Unit>);
    static_assert(std::is_nothrow_move_constructible_v<Unit>);
    static_assert(std::is_nothrow_destructible_v<Unit>);
    static_assert(std::is_nothrow_swappable_v<Unit>);

    static_assert(std::is_trivially_copy_constructible_v<Unit>);
    static_assert(std::is_trivially_move_constructible_v<Unit>);
    static_assert(std::is_trivially_destructible_v<Unit>);
} // namespace diplomacy
