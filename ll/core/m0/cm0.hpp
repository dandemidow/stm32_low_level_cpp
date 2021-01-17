#if !defined(CORE_CM0_HPP_)
#define CORE_CM0_HPP_

#include "register/nested_vectored_interrupt_controller.hpp"
#include "register/system_control_block.h"
#include "irqs.h"

namespace ll::nvic {

using address::nvic::PriorityGroup;

constexpr uint32_t BitShift(IRQn_Type irq) {
  return (static_cast<uint32_t>(irq) & 0b11) * 8u;
}

constexpr uint32_t ShpIndex(IRQn_Type irq) {
  return ((static_cast<uint32_t>(irq) & 0b1111) - 8ul) >> 2ul;
}

constexpr uint32_t IpIndex(IRQn_Type irq) {
  return static_cast<uint32_t>(irq) >> 2ul;
}

static inline void set_priority(IRQn_Type IRQn, uint32_t priority = 0u) {
  using address::nvic::kPrioBits;
  auto value = ((priority << (8U - kPrioBits)) & (uint32_t)0xfful) << BitShift(IRQn);
  if (static_cast<int>(IRQn) >= 0) {
    auto &nvic = *new NestedVectoredInterruptController{};
    const uint32_t irq_index = IpIndex(IRQn);
    nvic.get<nvic::IP>()[irq_index] = (nvic.get<nvic::IP>()[irq_index] & ~(0xfful << BitShift(IRQn))) | value;
  } else {
    auto &scb = *new SystemControlBlock{};
    const uint32_t irq_index = ShpIndex(IRQn);
    scb.get<scb::SHP>()[irq_index] = (scb.get<scb::SHP>()[irq_index] & ~(0xfful << BitShift(IRQn))) | value;
  }
}

static inline void enable_irq(IRQn_Type IRQn) {
  auto &nvic = *new NestedVectoredInterruptController{};
  nvic.get<ISER>()[0u] = static_cast<uint32_t>(1UL << (static_cast<uint32_t>(IRQn) & 0x1ful));
}

}  // namespace ll::nvic
#endif
