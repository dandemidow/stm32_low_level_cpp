#if !defined(TIM_HPP_)
#define TIM_HPP_

#include "addresses.h"
#include "device_register.h"
#include "module.h"

namespace ll::tim {
enum class index : uint32_t {
  T1 = address::tim::kT1,
  T3 = address::tim::kT3
};

namespace cr1 {

constexpr auto kCen = Flag<0x1u, 0u>{};
constexpr auto kDir = Flag<0x1u, 4u>{};
constexpr auto kCms = Flag<0x3u, 5u>{};
constexpr auto kArpe = Flag<0x1u, 7u>{};
constexpr auto kCkd = Flag<0x3u, 8u>{};

}  // namespace cr1

namespace egr {

constexpr auto kUg = Flag<0x1, 0u>{};

}  // namespace egr

namespace dier {

constexpr auto kUie = Flag<0x1u, 0u>{};

}  // namespace dier

namespace smcr {

constexpr auto kSms = Flag<0x7u, 0u>{};
constexpr auto kMsm = Flag<0x1u, 7u>{};
constexpr auto kEce = Flag<0x1u, 14u>{};

}  // namespace smcr

enum : uint32_t {
  CR1,
  CR2,
  SMCR,
  DIER,
  SR,
  EGR,
  CCMR1,
  CCMR2,
  CCER,
  CNT,
  PSC,
  ARR,
  RCR,
  CCR1,
  CCR2,
  CCR3,
  CCR4,
  BDTR,
  DCR,
  DMAR,
  OR
};

}  // namespace ll::tim

using Tim = Module<ll::tim::index,
Register,
Register,
Register,
Register,
Register,
Register,
Register,
Register,
Register,
Register,
Register,
Register,
Register,
Register,
Register,
Register,
Register,
Register,
Register,
Register,
Register
>;

static_assert(std::is_standard_layout<Tim>::value);

#endif
