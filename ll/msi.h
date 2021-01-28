#if !defined(LL_MSI_H_)
#define LL_MSI_H_

#include "rcc.hpp"

namespace ll {

class Msi {
  ResetClockControl &rcc;
 public:
  static constexpr auto kClk = rcc::cfgr::kSwClk<rcc::cfgr::SwClk::Msi>;
  Msi() : rcc {*new ResetClockControl{}} {}
  inline void Enable() {
    bit::set(rcc.get<rcc::CR>(), rcc::cr::kMsiOn);
  }

  inline bool IsReady() const {
    return ((bit::read(rcc.get<rcc::CR>(), rcc::cr::kMsiRdy) == rcc::cr::kMsiRdy) ? true : false);
  }

  inline void EnableRangeSelection() {
    bit::set(rcc.get<rcc::CR>(), rcc::cr::kMsiRgSel);
  }

  inline void SetRange(uint32_t range) {
    reg::modify(rcc.get<rcc::CR>(), rcc::cr::kMsiRange.value, range);
  }

  inline void SetCalibTrimming(uint32_t value) {
    reg::modify(rcc.get<rcc::ICSCR>(), rcc::kIcsCrMsiTrim.value, value << rcc::kIcsCrMsiTrim.position);
  }

  constexpr operator decltype(kClk)() const {
    return kClk;
  }

  operator rcc::SysClkSource() {
    return rcc::SysClkSource::Msi;
  }

  friend auto operator ==(rcc::SysClkSourceStatus source, const Msi &) {
    return source == rcc::SysClkSourceStatus::Msi;
  }

  friend auto operator !=(rcc::SysClkSourceStatus source, const Msi &) {
    return source != rcc::SysClkSourceStatus::Msi;
  }
};

}  // namespace ll

#endif
