#if !defined(LL_GPIO_INPUT_H_)
#define LL_GPIO_INPUT_H_

#include "pin.h"

namespace ll::gpio {

struct Input : public Pin {
  Input(port p, uint32_t number) : Pin{p, number} {}

  bool init(const gpio::pull &pull);
};

}  // namespace ll::gpio

#endif
