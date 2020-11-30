#if !defined(LL_UTILS_H_)
#define LL_UTILS_H_

#include "system_timer.hpp"

extern uint32_t SystemCoreClock;

namespace ll {

constexpr uint32_t kMaxDelay = 0xffffffffu;

static inline void init_tick(uint32_t HCLKFrequency, uint32_t Ticks) {
  auto &sys_tick = *new SystemTimer{};
  /* Configure the SysTick to have interrupt in 1ms time base */
  sys_tick.set<sys_tick::LOAD>(((HCLKFrequency / Ticks) - 1u));  // set reload register
  sys_tick.set<sys_tick::VAL>(0u);                                // Load the SysTick Counter Value
  sys_tick.set<sys_tick::CTRL>(sys_tick::ctrl::kClkSource.mask | sys_tick::ctrl::kEnable.mask); // Enable the Systick Timer
}


inline void init_1ms_tick(uint32_t HCLKFrequency) {
  /* Use frequency provided in argument */
  init_tick(HCLKFrequency, 1000U);
}

inline void set_system_core_clock(uint32_t HCLKFrequency) {
  /* HCLK clock frequency */
  SystemCoreClock = HCLKFrequency;
}

static void m_delay(uint32_t delay) {
  auto &sys_tick = *new SystemTimer{};
  [[maybe_unused]] uint32_t tmp = sys_tick.get<sys_tick::CTRL>();  /* Clear the COUNTFLAG first */
  uint32_t tmp_delay = delay;

  /* Add a period to guaranty minimum wait */
  if(tmp_delay < kMaxDelay) {
    tmp_delay++;
  }

  while (tmp_delay != 0u) {
    if (sys_tick.And<sys_tick::CTRL>(sys_tick::ctrl::kCountFlag.value) != 0U) {
      tmp_delay--;
    }
  }
}

}  // namespace ll

#endif