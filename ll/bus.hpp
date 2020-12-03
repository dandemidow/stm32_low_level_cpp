#if !defined(LL_BUS_H_)
#define LL_BUS_H_

#include <type_traits>

#include "reset_clock_control.h"

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
using tag = std::integral_constant<uint32_t, rcc::AHB1ENR>;
constexpr auto kGrp1PeriphPwr = BusValue<tag>{rcc::kApb1Enr1PwrEn};
}  // namespace apb1

namespace apb2 {
using tag = std::integral_constant<uint32_t, rcc::APB2ENR>;
constexpr auto kGrp1PeriphAll = BusValue<tag>{0xFFFFFFFFu};
constexpr auto kGrp1PeriphSysCfg = BusValue<tag>{rcc::kApb2EnrSysCfgEn};
}  // namespace apb2

namespace ahb2 {
using tag = std::integral_constant<uint32_t, rcc::AHB2ENR>;
constexpr auto kGrp1PeriphGpioA = BusValue<tag>{address::ahb2::kGrp1PeriphGpioA};
}  // namespace ahb2

template <typename Bus>
static inline void Grp1EnableClock(const BusValue<Bus> &periphs) {
  auto &rcc = *new ResetClockControl{};
  bit::set(rcc.get<Bus::value>(), periphs);
  bit::read(rcc.get<Bus::value>(), periphs);
}

}  // namespace ll::bus

#endif
