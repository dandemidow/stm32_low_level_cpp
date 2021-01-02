#if !defined(GPIO_BUS_H_)
#define GPIO_BUS_H_

#include "general_purpose_io.hpp"
#include "bus.hpp"

namespace ll::gpio {

inline auto EnablePort(const port &p) {
  switch (p) {
  case port::A: bus::GrpEnableClock(rcc::kAhb1Grp1PeriphGpioA); break;
  case port::B: bus::GrpEnableClock(rcc::kAhb1Grp1PeriphGpioB); break;
  case port::C: bus::GrpEnableClock(rcc::kAhb1Grp1PeriphGpioC); break;
  }
}

}  // namespace ll::gpio
#endif
