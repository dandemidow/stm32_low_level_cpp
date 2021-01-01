#if !defined(LL_BUS_H_)
#define LL_BUS_H_

#include <type_traits>

#include "register/reset_clock_control.h"

namespace ll::bus {

template <typename Bus>
struct BusValue {
  static constexpr uint32_t kBus = Bus::value;
  uint32_t value;
  operator uint32_t() const {
    return value;
  }
};

namespace apb1 {
constexpr auto kGrp1PeriphPwr = rcc::kApb1Enr1PwrEn;
}  // namespace apb1

namespace apb2 {
constexpr auto kGrp1PeriphSysCfg = rcc::kApb2EnrSysCfgEn;
constexpr auto kGrp1PeriphAll = rcc::kApb2PeriphAll;
}  // namespace apb2

namespace ahb2 {
using tag = std::integral_constant<uint32_t, rcc::AHB2ENR>;
constexpr auto kGrp1PeriphGpioA = BusValue<tag>{address::ahb2::kGrp1PeriphGpioA};
}  // namespace ahb2

template <uint32_t Reg>
static inline void GrpEnableClock(const RegisterValue<Reg> &periphs) {
  auto &rcc = *new ResetClockControl{};
  bit::set(rcc.get<Reg>(), periphs);
  bit::read(rcc.get<Reg>(), periphs);
}

}  // namespace ll::bus

#endif
