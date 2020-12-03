#if !defined(LL_BUS_H_)
#define LL_BUS_H_

#include <type_traits>

#include "reset_clock_control.h"

namespace ll::bus {

using Apb2 = std::integral_constant<int, 0>;
using Ahb2 = std::integral_constant<int, 1>;

namespace details {
constexpr auto DetectRccEnr(Apb2) {
  return rcc::APB2ENR;
}
constexpr auto DetectRccEnr(Ahb2) {
  return rcc::AHB2ENR;
}
}  // namespace details

template <typename Bus>
static inline void Grp1EnableClock(uint32_t periphs) {
  auto &rcc = *new ResetClockControl{};
  constexpr auto kRccEnr = details::DetectRccEnr(Bus{});
  bit::set(rcc.get<kRccEnr>(), periphs);
  bit::read(rcc.get<kRccEnr>(), periphs);
}

constexpr uint32_t kApb2Grp1PeriphAll = 0xFFFFFFFFu;
constexpr uint32_t kApb2Grp1PeriphSysCfg = rcc::kApb2EnrSysCfgEn;
constexpr uint32_t kApb1Grp1PeriphPwr = rcc::kApb1Enr1PwrEn;

}  // namespace ll::bus

#endif
