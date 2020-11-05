#if !defined(NESTED_VECTORED_INTERRUPT_CONTROLLER_H_)
#define NESTED_VECTORED_INTERRUPT_CONTROLLER_H_

#include "addresses.h"
#include "device_register.h"
#include "module.h"

constexpr uint32_t kNvicBaseAddress = kSystemControlSpaceBaseAddress + 0x0100ul;

namespace nvic {
 enum : uint32_t {
  ISER = 0u,
  RESERVED0,
  ICER,
  RESERVED1,
  ISPR,
  RESERVED2,
  ICPR,
  RESERVED3,
  IABR,
  RESERVED4,
  IP,
  RESERVED5,
  STIR
};
}  // namespace nvic

using NestedVectoredInterruptController = Module<kNvicBaseAddress,
Register[8u],
uint32_t[24u],  // 0
Register[8u],
uint32_t[24u],  // 1
Register[8u],
uint32_t[24u],  // 2
Register[8u],
uint32_t[24u],  // 3
Register[8u],
uint32_t[56u],  // 4
Register[240],
uint32_t[664u],  // 5
Register
>;

static_assert(std::is_standard_layout<NestedVectoredInterruptController>::value);

constexpr uint32_t kNvicPrioBits = 4u;       /*!< STM32L4XX uses 4 Bits for the Priority Levels */
//constexpr uint32_t kRccCrMsiOn = Flag<0x1u, 0u>::value;
//constexpr uint32_t kRccCrMsiRdy = Flag<0x1u, 1u>::value;

#endif
