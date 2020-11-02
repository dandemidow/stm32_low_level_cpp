#if !defined(LL_RCC_H_)
#define LL_RCC_H_

#include "reset_clock_control.h"

namespace ll {

static inline void rcc_msi_enable() {
  auto &rcc = *new ResetClockControl{};
  bit::set(rcc.get<rcc::CR>(), kRccCrMsiOn);
}

static inline bool rcc_msi_is_ready() {
  auto &rcc = *new ResetClockControl{};
  return ((bit::read(rcc.get<rcc::CR>(), kRccCrMsiRdy) == kRccCrMsiRdy) ? true : false);
}

}  // namespace ll

#endif
