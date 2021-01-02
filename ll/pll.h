#if !defined(LL_PLL_H_)
#define LL_PLL_H_

#include "rcc.hpp"

namespace ll {

class Pll {
  ResetClockControl &rcc;
 public:
  Pll(rcc::cfgr::PllSrc Source, rcc::cfgr::PllMul PLLMul) : rcc {*new ResetClockControl{}} {
    reg::modify(rcc.get<rcc::CFGR>(),
                rcc::cfgr::kPllSrc | rcc::cfgr::kPllMul,
                (static_cast<uint32_t>(Source) & rcc::cfgr::kPllSrc) | static_cast<uint32_t>(PLLMul));
    reg::modify(rcc.get<rcc::CFGR2>(), rcc::cfgr2::kPrediv, (static_cast<uint32_t>(Source) & rcc::cfgr2::kPrediv));
  }
  inline void Enable() {
    bit::set(rcc.get<rcc::CR>(), rcc::cr::kPllOn);
  }

  inline bool IsReady() const {
    return ((bit::read(rcc.get<rcc::CR>(), rcc::cr::kPllRdy) == rcc::cr::kPllRdy) ? true : false);
  }

  operator rcc::SysClkSource() {
    return rcc::SysClkSource::Pll;
  }

  friend auto operator ==(rcc::SysClkSourceStatus source, const Pll &) {
    return source == rcc::SysClkSourceStatus::Pll;
  }

  friend auto operator !=(rcc::SysClkSourceStatus source, const Pll &) {
    return source != rcc::SysClkSourceStatus::Pll;
  }
};

}  // namespace ll

#endif
