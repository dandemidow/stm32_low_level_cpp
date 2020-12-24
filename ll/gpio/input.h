#if !defined(LL_GPIO_INPUT_H_)
#define LL_GPIO_INPUT_H_

#include "pin.h"

namespace ll::gpio {

struct Input : public Pin {
  Input(port p, uint32_t number) : Pin{p, number} {
    switch (p) {
    case port::A: bus::Grp1EnableClock(bus::ahb2::kGrp1PeriphGpioA);
    }
  }

  bool init(const gpio::pull &pull);
};

}  // namespace ll::gpio

#endif
