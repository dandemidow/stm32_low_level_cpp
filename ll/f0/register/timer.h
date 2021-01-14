#if !defined(TIMER_H_)
#define TIMER_H_

#include "tim.hpp"
#include "bus.hpp"

namespace ll::tim {

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
