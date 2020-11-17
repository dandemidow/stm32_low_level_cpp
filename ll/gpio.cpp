#include "gpio.h"

namespace ll {

bool gpio_init(gpio::Pin &pin, const GPIOInitType &init) {
  /* Pin Mode configuration */
  pin.set_mode(init.Mode);

  if ((init.Mode == gpio::mode::Output) ||
      (init.Mode == gpio::mode::Analog)) {
        /* Speed mode configuration */
        pin.set_speed(init.Speed);
  }

  /* Pull-up Pull down resistor configuration*/
  gpio_set_pin_pull(pin, init.Pull);

  if (init.Mode == gpio::mode::Alternate) {
    /* Speed mode configuration */
    if (pin.value() < gpio::kPin8) {
      gpio_set_af_pin_0_7(pin, init.Alternate);
    } else {
      gpio_set_af_pin_8_15(pin, init.Alternate);
    }
  }

  if ((init.Mode == gpio::mode::Output) ||
      (init.Mode == gpio::mode::Alternate)) {
    /* Output mode configuration*/
    gpio_set_pin_output_type(pin, pin.value(), init.OutputType);
  }
  return true;
}

namespace gpio {

void Pin::set_mode(mode mode) {
  const uint32_t position_pin = number_ * 2u;
  reg::modify(gpio_.get<MODER>(),
              (kModerMode0 << position_pin),
              (static_cast<uint32_t>(mode) << position_pin));
}

void Pin::set_speed(gpio_speed speed) {
  const uint32_t position_pin = number_ * 2u;
  reg::modify(gpio_.get<OSPEEDR>(),
              (gpio::kOspeedrOspeed0 << position_pin),
              (static_cast<uint32_t>(speed) << position_pin));
}

}  // namespace gpio

}  // namespace ll

