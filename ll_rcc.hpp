#if !defined(LL_RCC_H_)
#define LL_RCC_H_

#include "reset_clock_control.h"

namespace ll {

using RccSysClkSourceStatus = rcc::cfgr::Sws;
using RccSysClkSource = rcc::cfgr::Sw;
using RccSysClkDiv = rcc::cfgr::HPre;
using RccApb1Div = rcc::cfgr::PPre;

static inline void rcc_msi_enable() {
  auto &rcc = *new ResetClockControl{};
  bit::set(rcc.get<rcc::CR>(), kRccCrMsiOn);
}

static inline bool rcc_msi_is_ready() {
  auto &rcc = *new ResetClockControl{};
  return ((bit::read(rcc.get<rcc::CR>(), kRccCrMsiRdy) == kRccCrMsiRdy) ? true : false);
}

static inline void rcc_msi_enable_range_selection() {
  auto &rcc = *new ResetClockControl{};
  bit::set(rcc.get<rcc::CR>(), kRccCrMsiRgSel);
}

static inline void rcc_msi_set_range(uint32_t range) {
  auto &rcc = *new ResetClockControl{};
  reg::modify(rcc.get<rcc::CR>(), kRccCrMsiRange.value, range);
}

static inline void rcc_msi_set_calib_trimming(uint32_t value) {
  auto &rcc = *new ResetClockControl{};
  reg::modify(rcc.get<rcc::ICSCR>(), kRccIcsCrMsiTrim.value, value << kRccIcsCrMsiTrim.position);
}

static inline void rcc_set_sys_clk_source(RccSysClkSource source) {
  auto &rcc = *new ResetClockControl{};
  reg::modify(rcc.get<rcc::CFGR>(), rcc::cfgr::kSw.value, static_cast<uint32_t>(source));
}

static inline RccSysClkSourceStatus rcc_get_sys_clk_source() {
  auto &rcc = *new ResetClockControl{};
  return static_cast<RccSysClkSourceStatus>(bit::read(rcc.get<rcc::CFGR>(), rcc::cfgr::kSws));
}

static inline void rcc_set_ahb_prescaler(RccSysClkDiv prescaler) {
  auto &rcc = *new ResetClockControl{};
  reg::modify(rcc.get<rcc::CFGR>(), rcc::cfgr::kHPre, static_cast<uint32_t>(prescaler));
}

static inline void rcc_set_apb1_prescaler(RccApb1Div prescaler) {
  auto &rcc = *new ResetClockControl{};
  reg::modify(rcc.get<rcc::CFGR>(), rcc::cfgr::kPPre1.value, static_cast<uint32_t>(prescaler));
}

}  // namespace ll

#endif
