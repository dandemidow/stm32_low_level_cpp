#if !defined(GPIO_BUS_HPP_)
#define GPIO_BUS_HPP_

#include "general_purpose_io.hpp"
#include "bus.hpp"

namespace ll::gpio {

auto EnablePort(const port &p) {
  switch (p) {
  case port::A: bus::GrpEnableClock(rcc::kGrp1PeriphGpioA);
  }
}

}  // namespace ll::gpio
#endif
