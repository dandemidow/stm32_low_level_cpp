#if !defined(LL_MSI_H_)
#define LL_MSI_H_

#include "rcc.hpp"

namespace ll {

class Msi {
  ResetClockControl &rcc;
 public:
  Msi() : rcc {*new ResetClockControl{}} {}
  inline void Enable() {
    bit::set(rcc.get<rcc::CR>(), rcc::kCrMsiOn);
  }

  inline bool IsReady() const {
    return ((bit::read(rcc.get<rcc::CR>(), rcc::kCrMsiRdy) == rcc::kCrMsiRdy) ? true : false);
  }

  inline void WaitForReady() {
    while(IsReady() != true) {
    }
  }

  inline void EnableRangeSelection() {
    bit::set(rcc.get<rcc::CR>(), rcc::kCrMsiRgSel);
  }

  inline void SetRange(uint32_t range) {
    reg::modify(rcc.get<rcc::CR>(), rcc::kCrMsiRange.value, range);
  }

  inline void SetCalibTrimming(uint32_t value) {
    reg::modify(rcc.get<rcc::ICSCR>(), rcc::kIcsCrMsiTrim.value, value << rcc::kIcsCrMsiTrim.position);
  }

  operator rcc::SysClkSource() {
    return rcc::SysClkSource::Msi;
  }

  friend auto operator !=(rcc::SysClkSourceStatus source, const Msi &) {
    return source != rcc::SysClkSourceStatus::Msi;
  }
};

}  // namespace ll

#endif
