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

constexpr auto CalcArr(uint32_t psc, uint32_t freq, uint32_t tim_clk = SystemCoreClock.count()) {
  uint32_t result = 0u;
  if ((tim_clk/(psc + 1u)) >= freq) {
    result = (tim_clk/(freq * (psc + 1u)) - 1u);
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

  inline auto GetPrescaler() {
    return tim_.get<PSC>();
  }

  inline auto SetAutoReload(uint32_t auto_reload) {
    tim_.set<ARR>(auto_reload);
  }

 private:
  Tim &tim_;
};

}  // namespace ll::tim
#endif
