#pragma once

#include <string>
#include <string_view>
#include <type_traits>

#include <fmt/format.h>

namespace diplomacy {
    class Region {
    public:
        enum class Type { land, coast, sea };

        Region() = delete;
        Region(std::string_view name, std::string_view abbr, bool isSc, Type type) noexcept
            : name_{name}, abbr_{abbr}, isSc_{isSc}, type_{type} {}

        [[nodiscard]] auto name() const noexcept { return name_; }
        [[nodiscard]] auto abbr() const noexcept { return abbr_; }
        [[nodiscard]] auto isSc() const noexcept { return isSc_; }
        [[nodiscard]] auto type() const noexcept { return type_; }

        void setType(Type type) noexcept { type_ = type; };
        void setSc(bool isSc) noexcept { isSc_ = isSc; };

    private:
        std::string name_ = {};
        std::string abbr_ = {};
        bool isSc_ = false;
        Type type_ = Type::land;
    };

    static_assert(!std::is_default_constructible_v<Region>);
    static_assert(std::is_copy_constructible_v<Region>);

    static_assert(std::is_nothrow_move_constructible_v<Region>);
    static_assert(std::is_nothrow_destructible_v<Region>);
    static_assert(std::is_nothrow_swappable_v<Region>);
} // namespace diplomacy

namespace fmt {
    template <>
    struct formatter<diplomacy::Region> {
        template <typename ParseContext>
        constexpr auto parse(ParseContext& context) {
            return context.begin();
        }

        template <typename FormatContext>
        auto format(diplomacy::Region const& r, FormatContext& context) {
            return format_to(context.begin(), "{} ({})", r.name(), r.abbr());
        }
    };
} // namespace fmt
