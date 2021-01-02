#if !defined(FLASH_HPP_)
#define FLASH_HPP_

#include "addresses.h"
#include "module.h"

using FlashBaseAddress = std::integral_constant<uint32_t, address::flash::kBaseAddress>;

namespace ll::flash {

enum : uint32_t {
  ACR = 0u,
  KEYR,
  OPTKEYR,
  SR,
  CR,
  AR,
  RESERVED,
  OBR,
  WRPR,
};

enum class AcrLatency : uint32_t {
  kAcrLatency0,
  kAcrLatency1
};

constexpr uint32_t kAcrLatency = Flag<0x1u, 0u>::value;

}  // namespace ll::flash

using Flash = Module<FlashBaseAddress,
Register,
Register,
Register,
Register,
Register,
Register,
uint32_t,
Register,
Register
>;

static_assert(std::is_standard_layout<Flash>::value);

#endif
