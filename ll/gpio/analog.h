#if !defined(LL_GPIO_ANALOG_H_)
#define LL_GPIO_ANALOG_H_

#include "pin.h"

namespace ll::gpio {

struct Analog : public Pin {
  Analog(port p, uint32_t number) : Pin{p, number} {}

  bool init(const gpio::pull &pull,
            const speed &speed);
};

}  // namespace ll::gpio

#endif
