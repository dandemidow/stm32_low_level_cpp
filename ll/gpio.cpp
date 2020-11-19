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
  pin.set_pull(init.Pull);

  switch(init.Mode) {
  case gpio::mode::Alternate:
    pin.set_af(init.Alternate);
    [[fallthrough]];
  case gpio::mode::Output:
    pin.set_output_type(pin.value(), init.OutputType);
    break;
  default: break;
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



}  // namespace gpio

}  // namespace ll

