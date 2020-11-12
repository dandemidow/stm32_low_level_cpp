#if !defined(SYSTEM_TIMER_H_)
#define SYSTEM_TIMER_H_

#include "addresses.h"
#include "device_register.h"
#include "module.h"

constexpr uint32_t kSysTickBaseAddress = kSystemControlSpaceBaseAddress + 0x0010ul;
using SysTickBaseAddress = std::integral_constant<uint32_t, kSysTickBaseAddress>;

namespace sys_tick {
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
}  // namespace sys_tick

using SystemTimer = Module<SysTickBaseAddress,
Register,
Register,
Register,
ReadOnlyRegister
>;

static_assert(std::is_standard_layout<SystemTimer>::value);

#endif
