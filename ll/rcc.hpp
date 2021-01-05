#if !defined(LL_RCC_H_)
#define LL_RCC_H_

#include "register/reset_clock_control.h"

namespace ll::rcc {

using SysClkSourceStatus = cfgr::SwsClk;
using SysClkSource = cfgr::SwClk;
using SysClkDiv = cfgr::HPreDiv;
using Apb1Div = cfgr::PPre1Div;
using Apb2Div = cfgr::PPre2Div;

class BaseClock {
 public:
  BaseClock() : rcc {*new ResetClockControl{}} {}

 protected:
  ResetClockControl &rcc;
};

class SystemClock : public BaseClock {
 public:
  SystemClock &operator <<(SysClkSource source) {
    reg::modify(rcc.get<rcc::CFGR>(), rcc::cfgr::kSw.value, static_cast<uint32_t>(source));
    return *this;
  }

  inline SysClkSourceStatus get_source() const {
    return static_cast<SysClkSourceStatus>(bit::read(rcc.get<rcc::CFGR>(), rcc::cfgr::kSws));
  }
};

class AdvancedHighPerformanceBus : public BaseClock {
 public:
  AdvancedHighPerformanceBus &operator <<(SysClkDiv prescaler) {
    reg::modify(rcc.get<rcc::CFGR>(), rcc::cfgr::kHPre, static_cast<uint32_t>(prescaler));
    return *this;
  }
};

class AdvancedPeripheralBus1 : public BaseClock {
 public:
  AdvancedPeripheralBus1 &operator <<(Apb1Div prescaler) {
    reg::modify(rcc.get<rcc::CFGR>(), rcc::cfgr::kPPre1.value, static_cast<uint32_t>(prescaler));
    return *this;
  }
};

class AdvancedPeripheralBus2 : public BaseClock {
 public:
  AdvancedPeripheralBus2 &operator <<(Apb2Div prescaler) {
    reg::modify(rcc.get<rcc::CFGR>(), rcc::cfgr::kPPre2.value, static_cast<uint32_t>(prescaler));
    return *this;
  }
};

}  // namespace ll::rcc

#endif
