#if !defined(LL_UTILS_H_)
#define LL_UTILS_H_

#include <chrono>
#include <limits>

#include "system_timer.hpp"
#include "frequency.h"

extern hertz SystemCoreClock;

namespace ll {
namespace tick {

static inline void init(const hertz &hclk, uint32_t Ticks) {
  auto &sys_tick = *new SystemTimer{};
  /* Configure the SysTick to have interrupt in 1ms time base */
  sys_tick.set<LOAD>(((hclk.count() / Ticks) - 1u));  // set reload register
  sys_tick.set<VAL>(0u);                                // Load the SysTick Counter Value
  sys_tick.set<CTRL>(ctrl::kClkSource.mask | ctrl::kEnable.mask); // Enable the Systick Timer
}

inline void init_1ms(const hertz &hclk) {
  /* Use frequency provided in argument */
  init(hclk, 1000U);
}

}  // namespace tick

inline void set_system_core_clock(const hertz &hclk) {
  /* HCLK clock frequency */
  SystemCoreClock = hclk;
}

static void delay(const std::chrono::milliseconds &delay) {
  constexpr auto kMaxDelay = std::numeric_limits<uint32_t>::max();
  auto &sys_tick = *new SystemTimer{};
  [[maybe_unused]] uint32_t tmp = sys_tick.get<tick::CTRL>();  /* Clear the COUNTFLAG first */
  auto tmp_delay = static_cast<uint32_t>(delay.count());

  /* Add a period to guaranty minimum wait */
  if(tmp_delay < kMaxDelay) {
    tmp_delay++;
  }

  while (tmp_delay != 0u) {
    if (sys_tick.And<tick::CTRL>(tick::ctrl::kCountFlag.value) != 0U) {
      tmp_delay--;
    }
  }
}

}  // namespace ll

#endif
