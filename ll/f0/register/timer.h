#if !defined(TIMER_H_)
#define TIMER_H_

#include "tim.hpp"
#include "bus.hpp"
#include "frequency.h"

extern hertz SystemCoreClock;

namespace ll::tim {

constexpr auto CalcPsc(uint32_t cnt_clk, uint32_t tim_clk = SystemCoreClock.count()) -> int {
  uint32_t result = 0u;
  if (tim_clk >= cnt_clk) {
    result = static_cast<uint32_t>(tim_clk/cnt_clk - 1u);
  }
  return result;
}

constexpr auto CalcArr(uint32_t psc, uint32_t freq, uint32_t tim_clk = SystemCoreClock.count()) {
  uint32_t result = 0u;
  if ((tim_clk/(psc + 1u)) >= freq) {
    result = (tim_clk/(freq * (psc + 1u)) - 1u);
  }
  return result;
}

class Timer {
 public:
  Timer(index i) : tim_{*new (i) Tim{}} {
  }

  auto Init(uint32_t counter_mode, uint32_t clock_div) {
    uint32_t tmpcr1 = tim_.get<CR1>();
    reg::modify(tmpcr1, cr1::kDir | cr1::kCms, counter_mode);
    reg::modify(tmpcr1, cr1::kCkd, clock_div);
    tim_.set<CR1>(tmpcr1);
  }

  inline auto SetPrescaler(uint32_t prescaler) {
    tim_.set<PSC>(prescaler);
  }

  inline auto GetPrescaler() {
    return tim_.get<PSC>();
  }

  inline auto SetAutoReload(uint32_t auto_reload) {
    tim_.set<ARR>(auto_reload);
  }

  inline auto SetRepetitionCounter(uint32_t repetition_counter) {
    tim_.set<RCR>(repetition_counter);
  }

  inline auto EnableItUpdate() {
    bit::set(tim_.get<DIER>(), dier::kUie);
  }

  inline auto DisableItUpdate() {
    bit::clear(tim_.get<DIER>(), dier::kUie);
  }

  inline void EnableCounter() {
    bit::set(tim_.get<CR1>(), cr1::kCen);
  }

  inline void DisableCounter() {
    bit::clear(tim_.get<CR1>(), cr1::kCen);
  }

  inline void GenerateEventUpdate() {
    bit::set(tim_.get<EGR>(), egr::kUg);
  }

  inline void EnableARRPreload() {
    bit::set(tim_.get<CR1>(), cr1::kArpe);
  }

  inline void DisableARRPreload() {
    bit::clear(tim_.get<CR1>(), cr1::kArpe);
  }

  inline void SetClockSource(uint32_t ClockSource) {
    reg::modify(tim_.get<SMCR>(), smcr::kSms | smcr::kEce, ClockSource);
  }

  inline void EnableMasterSlaveMode() {
    bit::set(tim_.get<SMCR>(), smcr::kMsm);
  }

  inline void DisableMasterSlaveMode() {
    bit::clear(tim_.get<SMCR>(), smcr::kMsm);
  }

 private:
  Tim &tim_;
};

}  // namespace ll::tim
#endif
