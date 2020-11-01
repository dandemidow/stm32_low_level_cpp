#if !defined(CORE_CM4_HPP_)
#define CORE_CM4_HPP_

#include "nested_vectored_interrupt_controller.hpp"
#include "system_control_block.h"

namespace nvic {

static inline void set_priority(int32_t IRQn, uint32_t priority) {
  if (IRQn >= 0) {
    auto &nvic = *new NestedVectoredInterruptController{};
    nvic.get<nvic::IP>()[static_cast<uint32_t>(IRQn)] = (uint8_t)((priority << (8u - kNvicPrioBits)) & 0xffu);
  } else {
    auto &scb = *new SystemControlBlock{};
    scb.get<scb::SHP>()[(static_cast<uint32_t>(IRQn) & 0xful)-4ul] = (uint8_t)((priority << (8u - kNvicPrioBits)) & (uint32_t)0xfful);
  }
}

static inline void set_priority_grouping(uint32_t priority_group) {
  auto &scb = *new SystemControlBlock{};
  uint32_t priority_group_tmp = (priority_group & (uint32_t)0x07u);            /* only values 0..7 are used          */

  uint32_t reg_value = scb.get<scb::AIRCR>();                                  /* read old register configuration    */
  reg_value &= ~((uint32_t)(kScbAircrVectKey.mask | kScbAircrPriGroup.mask));  /* clear bits to change               */
  reg_value  =  (reg_value |
                ((uint32_t)0x5faul << kScbAircrVectKey.position) |
                (priority_group_tmp << kScbAircrPriGroup.position));           /* Insert write key and priority group */
  scb.set<scb::AIRCR>(reg_value);
}

}  // namespace nvic
#endif
