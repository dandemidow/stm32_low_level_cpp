#include "input.h"

namespace ll::gpio {

bool Input::init(const pull &pull) {
  set_mode(mode::Input);
  set_pull(pull);
  return true;
}

}  // namespace ll::gpio
