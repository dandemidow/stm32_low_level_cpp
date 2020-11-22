#include "gpio.h"

namespace ll::gpio {

bool Pin::init(const init_cfg &init) {
  /* Pin Mode configuration */
  set_mode(init.Mode);

  if ((init.Mode == gpio::mode::Output) ||
      (init.Mode == gpio::mode::Analog)) {
        /* Speed mode configuration */
        set_speed(init.Speed);
  }

  /* Pull-up Pull down resistor configuration*/
  set_pull(init.Pull);

  switch(init.Mode) {
  case gpio::mode::Alternate:
    set_af(init.Alternate);
    [[fallthrough]];
  case gpio::mode::Output:
    set_output_type(value_, init.OutputType);
    break;
  default: break;
  }
  return true;
}


void Pin::set_mode(mode mode) {
  const uint32_t position_pin = number_ * 2u;
  reg::modify(gpio_.get<MODER>(),
              (kModerMode0 << position_pin),
              (static_cast<uint32_t>(mode) << position_pin));
}

}  // namespace ll::gpio

