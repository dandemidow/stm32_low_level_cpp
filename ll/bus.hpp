#if !defined(LL_BUS_H_)
#define LL_BUS_H_

#include <type_traits>

#include "register/reset_clock_control.h"

namespace ll::bus {

template <uint32_t Reg>
static inline void GrpEnableClock(const RegisterValue<Reg> &periphs) {
  auto &rcc = *new ResetClockControl{};
  bit::set(rcc.get<Reg>(), periphs);
  bit::read(rcc.get<Reg>(), periphs);
}

}  // namespace ll::bus

#endif
