#if !defined(GPIO_BUS_H_)
#define GPIO_BUS_H_

#include "general_purpose_io.hpp"
#include "bus.hpp"

namespace ll::gpio {

inline auto EnablePort(const port &p) {
  switch (p) {
  case port::A: bus::GrpEnableClock(rcc::kGrp1PeriphGpioA);
  }
}

}  // namespace ll::gpio
#endif
