#if !defined(FLASH_HPP_)
#define FLASH_HPP_

#include "addresses.h"
#include "device_register.h"
#include "module.h"

using FlashBaseAddress = std::integral_constant<uint32_t, address::flash::kBaseAddress>;

namespace flash {
 enum : uint32_t {
   ACR = 0u,
   PDKEYR,
   KEYR,
   OPTKEYR,
   SR,
   CR,
   ECCR,
   RESERVED1,
   OPTR,
   PCROP1SR,
   PCROP1ER,
   WRP1AR,
   WRP1BR
};
}  // namespace flash

using Flash = Module<FlashBaseAddress,
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
Register
>;

static_assert(std::is_standard_layout<Flash>::value);

#endif
