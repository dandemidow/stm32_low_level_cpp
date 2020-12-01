#if !defined(LL_CORTEX_HPP_)
#define LL_CORTEX_HPP_

#include "system_timer.hpp"

extern uint32_t SystemCoreClock;

namespace ll {
namespace tick {

static inline void sys_set_clk_source(uint32_t source) {
  auto &sys_tick = *new SystemTimer{};
  if (source == tick::kClkSourceHCLK) {
    bit::set(sys_tick.get<tick::CTRL>(), tick::kClkSourceHCLK);
  } else {
    bit::clear(sys_tick.get<tick::CTRL>(), tick::kClkSourceHCLK);
  }
}

}  // namespace tick
}  // namespace ll

#endif
