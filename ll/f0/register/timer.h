#if !defined(TIMER_H_)
#define TIMER_H_

#include "tim.hpp"
#include "bus.hpp"
#include "frequency.h"

extern hertz SystemCoreClock;

namespace ll::tim {

constexpr auto CalcPsc(uint32_t cnt_clk, uint32_t tim_clk = SystemCoreClock.count()) -> int {
  uint32_t result = 0u;
  if (tim_clk >= cnt_clk) {
    result = static_cast<uint32_t>(tim_clk/cnt_clk - 1u);
  }
  return result;
}

class Timer {
 public:
  Timer(index i) : tim_{*new (i) Tim{}} {
  }

  inline auto SetPrescaler(uint32_t prescaler) {
    tim_.set<PSC>(prescaler);
  }

 private:
  Tim &tim_;
};

}  // namespace ll::tim
#endif
