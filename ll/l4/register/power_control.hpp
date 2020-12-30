#if !defined(POWER_CONTROL_HPP_)
#define POWER_CONTROL_HPP_

#include "addresses.h"
#include "module.h"

using PowerBaseAddress = std::integral_constant<uint32_t, address::power::kBaseAddress>;

namespace ll::pwr {
 enum : uint32_t {
   CR1 = 0u,
   CR2,
   CR3,
   CR4,
   SR1,
   SR2,
   SCR,
   RESERVED,
   PUCRA,
   PDCRA,
   PUCRB,
   PDCRB,
   PUCRC,
   PDCRC,
   PUCRD,
   PDCRD,
   PUCRE,
   PDCRE,
   RESERVED1,
   RESERVED2,
   RESERVED3,
   RESERVED4,
   PUCRH,
   PDCRH
};
}  // namespace ll::pwr

using PowerControl = Module<PowerBaseAddress,
Register,
Register,
Register,
Register,
Register,
Register,
Register,
uint32_t,
Register,
Register,
Register,
Register,
Register,
Register,
Register,
Register,
Register,
Register,
uint32_t,
uint32_t,
uint32_t,
uint32_t,
Register,
Register
>;

static_assert(std::is_standard_layout<PowerControl>::value);

#endif
