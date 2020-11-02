#if !defined(RESET_CLOCK_CONTROL_H_)
#define RESET_CLOCK_CONTROL_H_

#include "addresses.h"
#include "device_register.h"
#include "module.h"

constexpr uint32_t kRccBaseAddress = kAhb1periphBaseAddress + 0x1000UL;

namespace rcc {
 enum : uint32_t {
  CR = 0u,          /*!< RCC clock control register,                                              Address offset: 0x00 */
  ICSCR,            /*!< RCC internal clock sources calibration register,                         Address offset: 0x04 */
  CFGR,             /*!< RCC clock configuration register,                                        Address offset: 0x08 */
  PLLCFGR,          /*!< RCC system PLL configuration register,                                   Address offset: 0x0C */
  PLLSAI1CFGR,      /*!< RCC PLL SAI1 configuration register,                                     Address offset: 0x10 */
  RESERVED,         /*!< Reserved,                                                                Address offset: 0x14 */
  CIER,             /*!< RCC clock interrupt enable register,                                     Address offset: 0x18 */
  CIFR,             /*!< RCC clock interrupt flag register,                                       Address offset: 0x1C */
  CICR,             /*!< RCC clock interrupt clear register,                                      Address offset: 0x20 */
  RESERVED0,        /*!< Reserved,                                                                Address offset: 0x24 */
  AHB1RSTR,         /*!< RCC AHB1 peripheral reset register,                                      Address offset: 0x28 */
  AHB2RSTR,         /*!< RCC AHB2 peripheral reset register,                                      Address offset: 0x2C */
  AHB3RSTR,         /*!< RCC AHB3 peripheral reset register,                                      Address offset: 0x30 */
  RESERVED1,        /*!< Reserved,                                                                Address offset: 0x34 */
  APB1RSTR1,        /*!< RCC APB1 peripheral reset register 1,                                    Address offset: 0x38 */
  APB1RSTR2,        /*!< RCC APB1 peripheral reset register 2,                                    Address offset: 0x3C */
  APB2RSTR,         /*!< RCC APB2 peripheral reset register,                                      Address offset: 0x40 */
  RESERVED2,        /*!< Reserved,                                                                Address offset: 0x44 */
  AHB1ENR,          /*!< RCC AHB1 peripheral clocks enable register,                              Address offset: 0x48 */
  AHB2ENR,          /*!< RCC AHB2 peripheral clocks enable register,                              Address offset: 0x4C */
  AHB3ENR,          /*!< RCC AHB3 peripheral clocks enable register,                              Address offset: 0x50 */
  RESERVED3,        /*!< Reserved,                                                                Address offset: 0x54 */
  APB1ENR1,         /*!< RCC APB1 peripheral clocks enable register 1,                            Address offset: 0x58 */
  APB1ENR2,         /*!< RCC APB1 peripheral clocks enable register 2,                            Address offset: 0x5C */
  APB2ENR,          /*!< RCC APB2 peripheral clocks enable register,                              Address offset: 0x60 */
  RESERVED4,        /*!< Reserved,                                                                Address offset: 0x64 */
  AHB1SMENR,        /*!< RCC AHB1 peripheral clocks enable in sleep and stop modes register,      Address offset: 0x68 */
  AHB2SMENR,        /*!< RCC AHB2 peripheral clocks enable in sleep and stop modes register,      Address offset: 0x6C */
  AHB3SMENR,        /*!< RCC AHB3 peripheral clocks enable in sleep and stop modes register,      Address offset: 0x70 */
  RESERVED5,        /*!< Reserved,                                                                Address offset: 0x74 */
  APB1SMENR1,       /*!< RCC APB1 peripheral clocks enable in sleep mode and stop modes register 1, Address offset: 0x78 */
  APB1SMENR2,       /*!< RCC APB1 peripheral clocks enable in sleep mode and stop modes register 2, Address offset: 0x7C */
  APB2SMENR,        /*!< RCC APB2 peripheral clocks enable in sleep mode and stop modes register, Address offset: 0x80 */
  RESERVED6,        /*!< Reserved,                                                                Address offset: 0x84 */
  CCIPR,            /*!< RCC peripherals independent clock configuration register,                Address offset: 0x88 */
  RESERVED7,        /*!< Reserved,                                                                Address offset: 0x8C */
  BDCR,             /*!< RCC backup domain control register,                                      Address offset: 0x90 */
  CSR,              /*!< RCC clock control & status register,                                     Address offset: 0x94 */
  CRRCR,            /*!< RCC clock recovery RC register,                                          Address offset: 0x98 */
  CCIPR2            /*!< RCC peripherals independent clock configuration register 2,              Address offset: 0x9C */
};

namespace cfgr {
enum class HPre {
  Div1   = 0x00000000u,
  Div2   = 0x00000080u,
  Div4   = 0x00000090u,
  Div8   = 0x000000a0u,
  Div16  = 0x000000b0u,
  Div64  = 0x000000c0u,
  Div128 = 0x000000d0u,
  Div256 = 0x000000e0u,
  Div512 = 0x000000f0u,
};

constexpr uint32_t kHPre = Flag<0xfu, 4u>::value;

enum class PPre1 {
  Div1   = 0x00000000u,
  Div2   = 0x00000400u,
  Div4   = 0x00000500u,
  Div8   = 0x00000600u,
  Div16  = 0x00000700u,
};

constexpr auto kPPre1 = Flag<0x7u, 8u>{};
template <uint32_t Index, std::enable_if_t<(Index >= 0 && Index <= 2), int> = 0>
constexpr uint32_t kPPre1By = Flag<2^Index, kPPre1.position>::value;

enum class PPre2 {
  Div1   = 0x00000000u,
  Div2   = 0x00002000u,
  Div4   = 0x00002800u,
  Div8   = 0x00003000u,
  Div16  = 0x00003800u,
};

constexpr auto kPPre2 = Flag<0x7u, 11u>{};

enum class Sw: uint32_t {
  Msi = 0x00000000u,  // MSI oscillator selection as system clock
  Hsi = 0x00000001u,  // HSI16 oscillator selection as system clock
  Hse = 0x00000002u,  // HSE oscillator selection as system clock
  Pll = 0x00000003u   // PLL selection as system clock
};

constexpr auto kSw = Flag<0x3u, 0u>{};
constexpr uint32_t kSw0 = Flag<0x1u, kSw.position>::value;
constexpr uint32_t kSw1 = Flag<0x2u, kSw.position>::value;

enum class Sws : uint32_t {
    Msi = 0x00000000u,
    Hsi = 0x00000004u,
    Hse = 0x00000008u,
    Pll = 0x0000000cu,
};

constexpr uint32_t kSws = Flag<0x3u, 2u>::value;

}  // namespace cfgr
}  // namespace rcc

using ResetClockControl = Module<kRccBaseAddress,
Register,
Register,
Register,
Register,
Register,
uint32_t,
Register,
Register,
Register,
uint32_t,
Register,
Register,
Register,
uint32_t,
Register,
Register,
Register,
uint32_t,
Register,
Register,
Register,
uint32_t,
Register,
Register,
Register,
uint32_t,
Register,
Register,
Register,
uint32_t,
Register,
Register,
Register,
uint32_t,
Register,
uint32_t,
Register,
Register,
Register,
Register
>;

static_assert(std::is_standard_layout<ResetClockControl>::value);

constexpr uint32_t kRccApb2EnrSysCfgEn = Flag<0x1u, 0u>::value;
constexpr uint32_t kRccApb1Enr1PwrEn = Flag<0x1u, 28u>::value;

/********************  Bit definition for RCC_CR register  ********************/
constexpr uint32_t kRccCrMsiOn = Flag<0x1u, 0u>::value;                  /*!< Internal Multi Speed oscillator (MSI) clock enable */
constexpr uint32_t kRccCrMsiRdy = Flag<0x1u, 1u>::value;                 /*!< Internal Multi Speed oscillator (MSI) clock ready flag */
constexpr uint32_t kRccCrMsiPllEn = Flag<0x1u, 2u>::value;               /*!< Internal Multi Speed oscillator (MSI) PLL enable */
constexpr uint32_t kRccCrMsiRgSel = Flag<0x1u, 3u>::value;               /*!< Internal Multi Speed oscillator (MSI) range selection */
constexpr auto kRccCrMsiRange = Flag<0xfu, 4u>{};               /*!< Internal Multi Speed oscillator (MSI) clock Range */
constexpr uint32_t kRccCsrMsiSRange = Flag<0xfu, 8u>::value;

constexpr uint32_t kRccPllCfgrPllSrc = Flag<0x3u, 0u>::value;
constexpr uint32_t kRccPllCfgrPllM = Flag<0x7u, 4u>::value;
constexpr uint32_t kRccPllCfgrPllN = Flag<0x7fu, 8u>::value;
constexpr uint32_t kRccPllCfgrPllR = Flag<0x3u, 25u>::value;

template <uint32_t Index>
constexpr uint32_t GetRccCrMsiRange() {
  constexpr uint32_t Lower = 0x0u;
  constexpr uint32_t Upper = 0xbu;
  static_assert ((Index >= Lower) && (Index <= Upper));
  return Flag<Index, kRccCrMsiRange.position>::value;
}

constexpr auto kRccIcsCrMsiTrim = Flag<0xffu, 8u>{};

#endif
