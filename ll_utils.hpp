#if !defined(LL_UTILS_H_)
#define LL_UTILS_H_

#include "system_timer.hpp"

namespace ll {

static inline void init_tick(uint32_t HCLKFrequency, uint32_t Ticks) {
  auto &sys_tick = *new SystemTimer{};
  /* Configure the SysTick to have interrupt in 1ms time base */
  sys_tick.set<sys_tick::LOAD>(((HCLKFrequency / Ticks) - 1u));  // set reload register
  sys_tick.set<sys_tick::VAL>(0u);                                // Load the SysTick Counter Value
  sys_tick.set<sys_tick::CTRL>(sys_tick::ctrl::kClkSource.mask | sys_tick::ctrl::kEnable.mask); // Enable the Systick Timer
}


void init_1ms_tick(uint32_t HCLKFrequency) {
  /* Use frequency provided in argument */
  init_tick(HCLKFrequency, 1000U);
}

void set_system_core_clock(uint32_t HCLKFrequency) {
  extern uint32_t SystemCoreClock;
  /* HCLK clock frequency */
  SystemCoreClock = HCLKFrequency;
}

}  // namespace ll

#endif
