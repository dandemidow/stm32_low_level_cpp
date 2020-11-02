#if !defined(POWER_CONTROL_HPP_)
#define POWER_CONTROL_HPP_

#include "addresses.h"
#include "device_register.h"
#include "module.h"

constexpr uint32_t kPowerBaseAddress = kApb1PeriphBaseAddress + 0x7000ul;

namespace pwr {
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
}  // namespace flash

using PowerControl = Module<kPowerBaseAddress,
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

constexpr uint32_t kPwrCr1Vos = Flag<0x3u, 9u>::value;
constexpr uint32_t kPwrCr1Vos0 = Flag<0x1u, 9u>::value;
constexpr uint32_t kPwrCr1Vos1 = Flag<0x2u, 9u>::value;

#endif
