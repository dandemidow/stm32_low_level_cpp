#include "analog.h"

namespace ll::gpio {

bool Analog::init(const pull &pull,
                 const speed &speed) {
  set_mode(mode::Analog);
  set_speed(speed);
  set_pull(pull);
  return true;
}

}  // namespace ll::gpio
