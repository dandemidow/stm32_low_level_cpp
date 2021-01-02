#if !defined(SYSTEM_TIMER_H_)
#define SYSTEM_TIMER_H_

#include "addresses.h"
#include "module.h"

using SysTickBaseAddress = std::integral_constant<uint32_t, address::tick::kBaseAddress>;

namespace ll::tick {
 enum : uint32_t {
  CTRL = 0u,
  LOAD,
  VAL,
  CALIB
};

namespace ctrl {
constexpr auto kCountFlag = Flag<0x1u, 16u>{};
constexpr auto kClkSource = Flag<0x1u, 2u>{};
constexpr auto kTickInt = Flag<0x1u, 1u>{};
constexpr auto kEnable = Flag<0x1u, 0u>{};
}  // namespace ctrl

constexpr uint32_t kClkSourceHCLK = ctrl::kClkSource.value;
}  // namespace ll::tick

using SystemTimer = Module<SysTickBaseAddress,
Register,
Register,
Register,
ReadOnlyRegister
>;

static_assert(std::is_standard_layout<SystemTimer>::value);

#endif
