#if !defined(GENERAL_PURPOSE_IO_HPP_)
#define GENERAL_PURPOSE_IO_HPP_

#include "addresses.h"
#include "device_register.h"
#include "module.h"

constexpr uint32_t kGpioABaseAddress = kAhb2PeriphBaseAddress + 0x0000ul;

enum class GpioAddresses : uint32_t {
  A =  kGpioABaseAddress
};

namespace gpio {
 enum : uint32_t {
   MODER,
   OTYPER,
   OSPEEDR,
   PUPDR,
   IDR,
   ODR,
   BSRR,
   LCKR,
   AFR,
   BRR
};

constexpr uint32_t kPin5 = Flag<0x1u, 5>::value;
}  // namespace flash

using GeneralPurposeIO = Module<GpioAddresses,
Register,
Register,
Register,
Register,
Register,
Register,
Register,
Register,
Register[2],
Register
>;

static_assert(std::is_standard_layout<GeneralPurposeIO>::value);


#endif
