#pragma once

#include <string>
#include <string_view>
#include <type_traits>

namespace diplomacy {
    class Region {
    public:
        enum class Type { land, coast, sea };

        Region() noexcept = default;
        Region(std::string_view name, std::string_view abbr, bool isSc, Type type) noexcept
            : name_{name}, abbr_{abbr}, isSc_{isSc}, type_{type} {}

        [[nodiscard]] auto name() const noexcept { return name_; }
        [[nodiscard]] auto abbr() const noexcept { return abbr_; }
        [[nodiscard]] auto isSc() const noexcept { return isSc_; }
        [[nodiscard]] auto type() const noexcept { return type_; }

    private:
        std::string name_ = {};
        std::string abbr_ = {};
        bool isSc_ = false;
        Type type_ = Type::land;
    };

    [[nodiscard]] bool operator==(Region const& lhs, Region const& rhs) noexcept;

    static_assert(std::is_nothrow_default_constructible_v<Region>);
    static_assert(std::is_copy_constructible_v<Region>);
    static_assert(std::is_nothrow_move_constructible_v<Region>);
    static_assert(std::is_nothrow_destructible_v<Region>);
    static_assert(std::is_nothrow_swappable_v<Region>);
} // namespace diplomacy
