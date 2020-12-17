#if !defined(LL_RCC_H_)
#define LL_RCC_H_

#include "reset_clock_control.h"

namespace ll::rcc {

using SysClkSourceStatus = ll::rcc::cfgr::Sws;
using SysClkSource = ll::rcc::cfgr::Sw;
using SysClkDiv = ll::rcc::cfgr::HPre;
using Apb1Div = rcc::cfgr::PPre1;
using Apb2Div = rcc::cfgr::PPre2;

class SystemClock {
 public:
  SystemClock() : rcc{*new ResetClockControl{}} {}

  SystemClock &operator <<(SysClkSource source) {
    reg::modify(rcc.get<rcc::CFGR>(), rcc::cfgr::kSw.value, static_cast<uint32_t>(source));
    return *this;
  }

  inline SysClkSourceStatus get_source() const {
    return static_cast<SysClkSourceStatus>(bit::read(rcc.get<rcc::CFGR>(), rcc::cfgr::kSws));
  }

 private:
  ResetClockControl &rcc;
};

static inline void set_ahb_prescaler(SysClkDiv prescaler) {
  auto &rcc = *new ResetClockControl{};
  reg::modify(rcc.get<rcc::CFGR>(), rcc::cfgr::kHPre, static_cast<uint32_t>(prescaler));
}

static inline void set_apb1_prescaler(Apb1Div prescaler) {
  auto &rcc = *new ResetClockControl{};
  reg::modify(rcc.get<rcc::CFGR>(), rcc::cfgr::kPPre1.value, static_cast<uint32_t>(prescaler));
}

static inline void set_apb2_prescaler(Apb2Div prescaler) {
  auto &rcc = *new ResetClockControl{};
  reg::modify(rcc.get<rcc::CFGR>(), rcc::cfgr::kPPre2.value, static_cast<uint32_t>(prescaler));
}

}  // namespace ll::rcc

#endif
