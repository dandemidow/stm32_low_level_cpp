#if !defined(LL_GPIO_OUTPUT_H_)
#define LL_GPIO_OUTPUT_H_

#include "pin.h"

namespace ll::gpio {

struct Output : public Pin {
  Output(port p, uint32_t number) : Pin{p, number} {
    switch (p) {
    case port::A: bus::Grp1EnableClock(bus::ahb2::kGrp1PeriphGpioA);
    }
    reset();
  }
  inline void reset() {
    gpio_.set<BRR>(value_);
  }

  bool init(const gpio::output &out_type,
            const gpio::pull &pull,
            const gpio::speed &speed);
};

}  // namespace ll::gpio

#endif
