#if !defined(RESET_CLOCK_CONTROL_H_)
#define RESET_CLOCK_CONTROL_H_

#include "addresses.h"
#include "module.h"

using RccBaseAddress = std::integral_constant<uint32_t, address::rcc::kBaseAddress>;

namespace ll::rcc {
 enum : uint32_t {
     CR = 0u,    /*!< RCC clock control register,                                   Address offset: 0x00 */
     CFGR,       /*!< RCC clock configuration register,                            Address offset: 0x04 */
     CIR,        /*!< RCC clock interrupt register,                                Address offset: 0x08 */
     APB2RSTR,   /*!< RCC APB2 peripheral reset register,                          Address offset: 0x0C */
     APB1RSTR,   /*!< RCC APB1 peripheral reset register,                          Address offset: 0x10 */
     AHBENR,     /*!< RCC AHB peripheral clock register,                           Address offset: 0x14 */
     APB2ENR,    /*!< RCC APB2 peripheral clock enable register,                   Address offset: 0x18 */
     APB1ENR,    /*!< RCC APB1 peripheral clock enable register,                   Address offset: 0x1C */
     BDCR,       /*!< RCC Backup domain control register,                          Address offset: 0x20 */
     CSR,        /*!< RCC clock control & status register,                         Address offset: 0x24 */
     AHBRSTR,    /*!< RCC AHB peripheral reset register,                           Address offset: 0x28 */
     CFGR2,      /*!< RCC clock configuration register 2,                          Address offset: 0x2C */
     CFGR3,      /*!< RCC clock configuration register 3,                          Address offset: 0x30 */
     CR2         /*!< RCC clock control register 2,                                Address offset: 0x34 */
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

/*!< ADCPPRE configuration */
constexpr uint32_t kPllSrcHsePrediv = 0x00010000u;

constexpr uint32_t kPllSrc = Flag<0x1u, 16u>::value;
constexpr uint32_t kPllMul = Flag<0xfu, 18u>::value;

}  // namespace cfgr

namespace cfgr2 {

constexpr uint32_t kPrediv = Flag<0xfu, 0u>::value;

}  // namespace cfgr2

constexpr uint32_t kApb2EnrSysCfgEn = Flag<0x1u, 0u>::value;
constexpr uint32_t kApb1Enr1PwrEn = Flag<0x1u, 28u>::value;

constexpr uint32_t kCrMsiOn = Flag<0x1u, 0u>::value;                  /*!< Internal Multi Speed oscillator (MSI) clock enable */
constexpr uint32_t kCrMsiRdy = Flag<0x1u, 1u>::value;                 /*!< Internal Multi Speed oscillator (MSI) clock ready flag */
constexpr uint32_t kCrMsiPllEn = Flag<0x1u, 2u>::value;               /*!< Internal Multi Speed oscillator (MSI) PLL enable */
constexpr uint32_t kCrMsiRgSel = Flag<0x1u, 3u>::value;               /*!< Internal Multi Speed oscillator (MSI) range selection */
constexpr auto kCrMsiRange = Flag<0xfu, 4u>{};               /*!< Internal Multi Speed oscillator (MSI) clock Range */
constexpr uint32_t kCsrMsiSRange = Flag<0xfu, 8u>::value;

constexpr uint32_t kPllCfgrPllSrc = Flag<0x3u, 0u>::value;
constexpr uint32_t kPllCfgrPllM = Flag<0x7u, 4u>::value;
constexpr uint32_t kPllCfgrPllN = Flag<0x7fu, 8u>::value;
constexpr uint32_t kPllCfgrPllR = Flag<0x3u, 25u>::value;

template <uint32_t Index>
constexpr uint32_t GetRccCrMsiRange() {
  constexpr uint32_t Lower = 0x0u;
  constexpr uint32_t Upper = 0xbu;
  static_assert ((Index >= Lower) && (Index <= Upper));
  return Flag<Index, kCrMsiRange.position>::value;
}

constexpr auto kIcsCrMsiTrim = Flag<0xffu, 8u>{};
}  // namespace ll::rcc

using ResetClockControl = Module<RccBaseAddress,
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
Register,
Register,
Register,
Register
>;

static_assert(std::is_standard_layout<ResetClockControl>::value);

#endif
