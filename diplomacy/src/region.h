#pragma once

#include <string>
#include <string_view>
#include <type_traits>

namespace diplomacy {
    class Region {
    public:
        enum class Type { land, coast, sea };

        Region() noexcept = default;
        Region(std::string_view name, bool isSc, Type type)
            : name_{name}, isSc_{isSc}, type_{type} {}

        [[nodiscard]] auto name() const { return name_; }
        [[nodiscard]] auto isSc() const noexcept { return isSc_; }
        [[nodiscard]] auto type() const noexcept { return type_; }

    private:
        std::string name_ = {};
        bool isSc_ = false;
        Type type_ = Type::land;
    };

    static_assert(std::is_nothrow_default_constructible_v<Region>);
    static_assert(std::is_copy_constructible_v<Region>);
    static_assert(std::is_nothrow_move_constructible_v<Region>);
    static_assert(std::is_nothrow_destructible_v<Region>);
    static_assert(std::is_nothrow_swappable_v<Region>);
} // namespace diplomacy
