#include "region.h"

namespace diplomacy {
    [[nodiscard]] bool operator==(Region const& lhs, Region const& rhs) noexcept {
        return lhs.abbr() == rhs.abbr();
    }
} // namespace diplomacy
