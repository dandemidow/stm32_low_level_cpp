#if !defined(LL_BUS_H_)
#define LL_BUS_H_

#include "device_register.h"
#include "reset_clock_control.h"

namespace ll {

static inline void Apb2Grp1EnableClock(uint32_t periphs) {
  auto &rcc = *new ResetClockControl{};
  bit::set(rcc.get<rcc::APB2ENR>(), periphs);
  bit::read(rcc.get<rcc::APB2ENR>(), periphs);
}

}  // namespace ll

#endif
