#if !defined(GENERAL_PURPOSE_IO_HPP_)
#define GENERAL_PURPOSE_IO_HPP_

#include "addresses.h"
#include "device_register.h"
#include "module.h"

constexpr uint32_t kGpioABaseAddress = kAhb2PeriphBaseAddress + 0x0000ul;

namespace ll::gpio {
enum class port : uint32_t {
  A = kGpioABaseAddress
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

constexpr uint32_t kModerMode0  = Flag<0x3u, 0u>::value;
constexpr uint32_t kModerMode00 = Flag<0x1u, 0u>::value;
constexpr uint32_t kModerMode01 = Flag<0x2u, 0u>::value;

constexpr uint32_t kOspeedrOspeed0  = Flag<0x3u, 0u>::value;
constexpr uint32_t kOspeedrOspeed00 = Flag<0x1u, 0u>::value;
constexpr uint32_t kOspeedrOspeed01 = Flag<0x2u, 0u>::value;

constexpr uint32_t kPupdrPupd0  = Flag<0x3u, 0u>::value;
constexpr uint32_t kPupdrPupd00 = Flag<0x1u, 0u>::value;
constexpr uint32_t kPupdrPupd01 = Flag<0x2u, 0u>::value;

constexpr uint32_t kAfrlAfsel0 = Flag<0xfu, 0u>::value;

constexpr uint32_t kAfrlAfsel8 = Flag<0xfu, 0u>::value;

constexpr uint32_t kOTypeR0 = Flag<0x1u, 0u>::value;

constexpr uint32_t kPin5 = Flag<0x1u, 5u>::value;
constexpr uint32_t kPin8 = Flag<0x1u, 8u>::value;
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
