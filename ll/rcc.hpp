#if !defined(LL_RCC_H_)
#define LL_RCC_H_

#include <compare>

#include "reset_clock_control.h"

namespace ll::rcc {

using SysClkSourceStatus = ll::rcc::cfgr::Sws;
using SysClkSource = ll::rcc::cfgr::Sw;
using SysClkDiv = ll::rcc::cfgr::HPre;
using Apb1Div = rcc::cfgr::PPre1;
using Apb2Div = rcc::cfgr::PPre2;

class Msi {
  ResetClockControl &rcc;
 public:
  Msi() : rcc {*new ResetClockControl{}} {}
  inline void Enable() {
    bit::set(rcc.get<rcc::CR>(), kCrMsiOn);
  }

  inline bool IsReady() const {
    return ((bit::read(rcc.get<rcc::CR>(), kCrMsiRdy) == kCrMsiRdy) ? true : false);
  }

  inline void EnableRangeSelection() {
    bit::set(rcc.get<rcc::CR>(), kCrMsiRgSel);
  }

  inline void SetRange(uint32_t range) {
    reg::modify(rcc.get<rcc::CR>(), kCrMsiRange.value, range);
  }

  inline void SetCalibTrimming(uint32_t value) {
    reg::modify(rcc.get<rcc::ICSCR>(), kIcsCrMsiTrim.value, value << kIcsCrMsiTrim.position);
  }

  operator SysClkSource() {
    return SysClkSource::Msi;
  }

  friend auto operator !=(SysClkSourceStatus source, const ll::rcc::Msi &) {
    return source != SysClkSourceStatus::Msi;
  }
};

static inline void set_sys_clk_source(SysClkSource source) {
  auto &rcc = *new ResetClockControl{};
  reg::modify(rcc.get<rcc::CFGR>(), rcc::cfgr::kSw.value, static_cast<uint32_t>(source));
}

static inline SysClkSourceStatus get_sys_clk_source() {
  auto &rcc = *new ResetClockControl{};
  return static_cast<SysClkSourceStatus>(bit::read(rcc.get<rcc::CFGR>(), rcc::cfgr::kSws));
}

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
