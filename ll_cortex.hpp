#if !defined(LL_CORTEX_HPP_)
#define LL_CORTEX_HPP_

#include "system_timer.hpp"

extern uint32_t SystemCoreClock;

namespace ll {

static inline void sys_tick_set_clk_source(uint32_t source) {
  auto &sys_tick = *new SystemTimer{};
  if (source == sys_tick::kClkSourceHCLK) {
    bit::set(sys_tick.get<sys_tick::CTRL>(), sys_tick::kClkSourceHCLK);
  } else {
    bit::clear(sys_tick.get<sys_tick::CTRL>(), sys_tick::kClkSourceHCLK);
  }
}

}  // namespace ll

#endif
