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

constexpr auto kCen = Flag<1u, 0u>{};

}  // namespace cr1

namespace dier {

constexpr auto kUie = Flag<1u, 0u>{};

}  // namespace dier

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
