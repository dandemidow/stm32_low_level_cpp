#if !defined(NESTED_VECTORED_INTERRUPT_CONTROLLER_H_)
#define NESTED_VECTORED_INTERRUPT_CONTROLLER_H_

#include "addresses.h"
#include "module.h"

using NvicBaseAddress = std::integral_constant<uint32_t, address::nvic::kBaseAddress>;

namespace ll::nvic {
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
}  // namespace ll::nvic

using NestedVectoredInterruptController = Module<NvicBaseAddress,
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

#endif
