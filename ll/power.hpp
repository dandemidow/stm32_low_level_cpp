#if !defined(LL_POWER_H_)
#define LL_POWER_H_

#include "power_control.hpp"

namespace ll {

namespace power {

static inline void set_regul_voltage_scaling(uint32_t voltage_scaling) {
  auto &pwr = *new PowerControl{};
  reg::modify(pwr.get<pwr::CR1>(), kPwrCr1Vos, voltage_scaling);
}

constexpr uint32_t kReguVoltageScale1 = kPwrCr1Vos0;
constexpr uint32_t kReguVoltageScale2 = kPwrCr1Vos1;

}  // namespace pwr

}  // namespace ll

#endif
