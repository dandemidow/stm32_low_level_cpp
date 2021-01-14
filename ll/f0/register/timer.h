#if !defined(TIMER_H_)
#define TIMER_H_

#include "tim.hpp"
#include "bus.hpp"

namespace ll::tim {

#define __LL_TIM_CALC_PSC(__TIMCLK__, __CNTCLK__)   \
   ((__TIMCLK__) >= (__CNTCLK__)) ? (uint32_t)((__TIMCLK__)/(__CNTCLK__) - 1U) : 0U

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
