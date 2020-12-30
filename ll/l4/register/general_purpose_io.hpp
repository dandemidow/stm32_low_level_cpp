#if !defined(GENERAL_PURPOSE_IO_HPP_)
#define GENERAL_PURPOSE_IO_HPP_

#include "addresses.h"
#include "device_register.h"
#include "module.h"

namespace ll::gpio {
enum class port : uint32_t {
  A = address::gpio::kPortA
};

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

}  // namespace ll::gpio

using GeneralPurposeIO = Module<ll::gpio::port,
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
