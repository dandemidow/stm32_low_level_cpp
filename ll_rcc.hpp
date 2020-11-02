#if !defined(LL_RCC_H_)
#define LL_RCC_H_

#include "reset_clock_control.h"

namespace ll {

enum class RccSysClkSourceStatus {
  Msi = RccCfgrSws::Msi,
  Hsi = RccCfgrSws::Hsi,
  Hse = RccCfgrSws::Hse,
  Pll = RccCfgrSws::Pll
};

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

static inline void rcc_set_sys_clk_source(uint32_t source) {
  auto &rcc = *new ResetClockControl{};
  reg::modify(rcc.get<rcc::CFGR>(), kRccCfgrSw.value, source);
}

static inline RccSysClkSourceStatus rcc_get_sys_clk_source() {
  auto &rcc = *new ResetClockControl{};
  return static_cast<RccSysClkSourceStatus>(bit::read(rcc.get<rcc::CFGR>(), kRccCfgrSws));
}

constexpr uint32_t kSysClkSourceMsi = kRccCfgrSwMsi;
constexpr uint32_t kSysClkSourceHsi = kRccCfgrSwHsi;
constexpr uint32_t kSysClkSourceHse = kRccCfgrSwHse;
constexpr uint32_t kSysClkSourcePll = kRccCfgrSwPll;

}  // namespace ll

#endif
