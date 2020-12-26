#include "output.h"

namespace ll::gpio {

bool Output::init(const output &out_type,
                  const pull &pull,
                  const speed &speed) {
    set_mode(mode::Output);
    set_speed(speed);
    set_pull(pull);
    set_output_type(value_, out_type);
    return true;
}

}  // namespace ll::gpio
