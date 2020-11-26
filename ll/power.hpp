#if !defined(LL_POWER_H_)
#define LL_POWER_H_

#include "power_control.hpp"

namespace ll {

namespace power {
using namespace address::power;

enum class ReguVoltage : uint32_t {
  kScale1 = kCr1Vos0,
  kScale2 = kCr1Vos1
};

static inline void set_regul_voltage_scaling(ReguVoltage voltage_scaling) {
  auto &pwr = *new PowerControl{};
  reg::modify(pwr.get<pwr::CR1>(), kCr1Vos, static_cast<uint32_t>(voltage_scaling));
}

}  // namespace power

}  // namespace ll

#endif
