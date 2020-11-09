#if !defined(LL_GPIO_H_)
#define LL_GPIO_H_

#include "general_purpose_io.hpp"

namespace ll {

static inline void gpio_reset_output_pin(GeneralPurposeIO &gpio, uint32_t pin) {
  gpio.set<gpio::BRR>(pin);
}

}  // namespace ll

#endif
