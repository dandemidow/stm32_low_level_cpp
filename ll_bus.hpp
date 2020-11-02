#if !defined(LL_BUS_H_)
#define LL_BUS_H_

#include "reset_clock_control.h"

namespace ll {

static inline void Apb2Grp1EnableClock(uint32_t periphs) {
  auto &rcc = *new ResetClockControl{};
  bit::set(rcc.get<rcc::APB2ENR>(), periphs);
  bit::read(rcc.get<rcc::APB2ENR>(), periphs);
}

constexpr uint32_t kApb2Grp1PeriphAll = 0xFFFFFFFFu;
constexpr uint32_t kApb2Grp1PeriphSysCfg = kRccApb2EnrSysCfgEn;
constexpr uint32_t kApb1Grp1PeriphPwr = kRccApb1Enr1PwrEn;

}  // namespace ll

#endif
