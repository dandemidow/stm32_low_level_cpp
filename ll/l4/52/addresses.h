#if !defined(L4_52_ADDRESSES_H_)
#define L4_52_ADDRESSES_H_

#include <cstdint>

#include "device_register.h"

constexpr uint32_t kPeriphBaseAddress = 0x40000000UL;  // Peripheral base address
constexpr uint32_t kApb1PeriphBaseAddress = kPeriphBaseAddress;
constexpr uint32_t kAhb1periphBaseAddress = kPeriphBaseAddress + 0x00020000ul;
constexpr uint32_t kAhb2PeriphBaseAddress = kPeriphBaseAddress + 0x08000000ul;

constexpr uint32_t kSystemControlSpaceBaseAddress = 0xE000E000ul;

namespace address {
namespace gpio {
constexpr uint32_t kPortA = kAhb2PeriphBaseAddress + 0x0000ul;

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
}  // namespace gpio

namespace flash {
constexpr uint32_t kBaseAddress = kAhb1periphBaseAddress + 0x2000ul;

constexpr uint32_t kAcrLatency = Flag<0x7u, 0u>::value;
}  // namespace flash

namespace power {
constexpr uint32_t kBaseAddress = kApb1PeriphBaseAddress + 0x7000ul;

constexpr uint32_t kCr1Vos = Flag<0x3u, 9u>::value;
constexpr uint32_t kCr1Vos0 = Flag<0x1u, 9u>::value;
constexpr uint32_t kCr1Vos1 = Flag<0x2u, 9u>::value;
}  // namespace power

namespace rcc {
constexpr uint32_t kBaseAddress = kAhb1periphBaseAddress + 0x1000UL;
}  // namespace rcc

namespace tick {
constexpr uint32_t kBaseAddress = kSystemControlSpaceBaseAddress + 0x0010ul;
}  // namespace tick
}  // namespace address

#endif
