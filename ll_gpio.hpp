#if !defined(LL_GPIO_H_)
#define LL_GPIO_H_

#include "general_purpose_io.hpp"
#include "cmsis_compiler.h"

#define POSITION_VAL(VAL)     (__CLZ(__RBIT(VAL)))

namespace ll {

static inline void gpio_reset_output_pin(GeneralPurposeIO &gpio, uint32_t pin) {
  gpio.set<gpio::BRR>(pin);
}

static inline void gpio_set_pin_mode(GeneralPurposeIO &gpio, uint32_t pin, uint32_t mode) {
  const uint32_t position_pos = POSITION_VAL(pin) * 2u;
  reg::modify(gpio.get<gpio::MODER>(),
              (gpio::kModerMode0 << position_pos),
              (mode << position_pos));
}

static inline void gpio_set_pin_speed(GeneralPurposeIO &gpio, uint32_t pin, uint32_t  speed) {
  const uint32_t position_pos = POSITION_VAL(pin) * 2u;
  reg::modify(gpio.get<gpio::OSPEEDR>(),
              (gpio::kOspeedrOspeed0 << position_pos),
              (speed << position_pos));
}

static inline void gpio_set_pin_pull(GeneralPurposeIO &gpio, uint32_t pin, uint32_t pull) {
  const uint32_t position_pos = POSITION_VAL(pin) * 2u;
  reg::modify(gpio.get<gpio::PUPDR>(),
              (gpio::kPupdrPupd0 << position_pos),
              (pull << position_pos));
}

}  // namespace ll

#endif
