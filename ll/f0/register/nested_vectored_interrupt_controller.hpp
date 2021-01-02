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
  RESERVED4,
  IP
};
}  // namespace ll::nvic

using NestedVectoredInterruptController = Module<NvicBaseAddress,
Register[1u],   // ISER
uint32_t[31u],  // 0
Register[1u],   // ICER
uint32_t[31u],  // 1
Register[1u],   // ISPR
uint32_t[31u],  // 2
Register[1u],   // ICPR
uint32_t[31u],  // 3
uint32_t[64u],  // 4
Register[8u]    // IP
>;

static_assert(std::is_standard_layout<NestedVectoredInterruptController>::value);

#endif
