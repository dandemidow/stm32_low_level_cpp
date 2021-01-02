#if !defined(LL_MSI_H_)
#define LL_MSI_H_

#include "rcc.hpp"

namespace ll {

class Hsi {
  ResetClockControl &rcc;
 public:
  Hsi() : rcc {*new ResetClockControl{}} {}
  inline void Enable() {
    bit::set(rcc.get<rcc::CR>(), rcc::cr::kHsiOn);
  }

  inline bool IsReady() const {
    return ((bit::read(rcc.get<rcc::CR>(), rcc::cr::kHsiRdy) == rcc::cr::kHsiRdy) ? true : false);
  }

  inline void SetCalibTrimming(const rcc::cr::HsiTrim &trim) {
    reg::modify(rcc.get<rcc::CR>(), rcc::cr::kHsiTrim, static_cast<uint32_t>(trim));
  }

  operator rcc::SysClkSource() {
    return rcc::SysClkSource::Hsi;
  }

  friend auto operator ==(rcc::SysClkSourceStatus source, const Hsi &) {
    return source == rcc::SysClkSourceStatus::Hsi;
  }

  friend auto operator !=(rcc::SysClkSourceStatus source, const Hsi &) {
    return source != rcc::SysClkSourceStatus::Hsi;
  }
};

}  // namespace ll

#endif
