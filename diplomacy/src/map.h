#pragma once

#include "region.h"

#include <filesystem>
#include <unordered_map>
#include <vector>

namespace diplomacy {
    class Map {
    public:
        Map() = default;
        Map(std::filesystem::path const& json);

    private:
        std::vector<std::unique_ptr<Region>> regions_ = {};
        std::unordered_multimap<Region*, Region*> borders_ = {};
    };

    static_assert(std::is_nothrow_default_constructible_v<Region>);
    static_assert(std::is_copy_constructible_v<Region>);
    static_assert(std::is_nothrow_move_constructible_v<Region>);
    static_assert(std::is_nothrow_destructible_v<Region>);
    static_assert(std::is_nothrow_swappable_v<Region>);
} // namespace diplomacy
