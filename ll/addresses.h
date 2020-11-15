#if !defined(ADDRESSES_H_)
#define ADDRESSES_H_

#include <cstdint>

constexpr uint32_t kPeriphBaseAddress = 0x40000000UL;  // Peripheral base address
constexpr uint32_t kApb1PeriphBaseAddress = kPeriphBaseAddress;
constexpr uint32_t kAhb1periphBaseAddress = kPeriphBaseAddress + 0x00020000ul;
constexpr uint32_t kAhb2PeriphBaseAddress = kPeriphBaseAddress + 0x08000000ul;

constexpr uint32_t kSystemControlSpaceBaseAddress = 0xE000E000ul;

#endif
