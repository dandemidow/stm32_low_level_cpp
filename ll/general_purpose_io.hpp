#if !defined(GENERAL_PURPOSE_IO_HPP_)
#define GENERAL_PURPOSE_IO_HPP_

#include "addresses.h"
#include "device_register.h"
#include "module.h"
#include <functional>

constexpr uint32_t kGpioABaseAddress = kAhb2PeriphBaseAddress + 0x0000ul;

namespace gpio {
enum class port : uint32_t {
  A =  kGpioABaseAddress
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
}  // namespace flash

using GeneralPurposeIO = Module<gpio::port,
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

namespace gpio {
class Pin {
 public:
  Pin(gpio::port p, uint32_t number)
    : gpio_ {*new (p) GeneralPurposeIO{}},
      number_ {number},
      value_ {0x01u << number} {}

  uint32_t position() const {
    return number_;
  }

  uint32_t value() const {
    return value_;
  }

  GeneralPurposeIO &port() {
    return gpio_;
  }

 private:
  GeneralPurposeIO &gpio_;
  const uint32_t number_;
  const uint32_t value_;
};
} // namespace gpio

#endif
