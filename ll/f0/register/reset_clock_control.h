#if !defined(RESET_CLOCK_CONTROL_H_)
#define RESET_CLOCK_CONTROL_H_

#include "addresses.h"
#include "module.h"
#include "register_value.hpp"

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
constexpr auto kSw = Flag<0x3u, 0u>{};
enum class Sw: uint32_t {
  Sw0 = kSw.Make(0x1u),
  Sw1 = kSw.Make(0x2u)
};
enum class SwClk: uint32_t {
  Hsi = 0x00000000u,
  Hse = static_cast<uint32_t>(Sw::Sw0),
  Pll = static_cast<uint32_t>(Sw::Sw1)
};
constexpr auto kSws = Flag<0x3u, 2u>{};
enum class Sws: uint32_t {
  Sws0 = kSws.Make(0x1u),
  Sws1 = kSws.Make(0x2u)
};
enum class SwsClk : uint32_t {
  Hsi = 0x00000000u,
  Hse = static_cast<uint32_t>(Sws::Sws0),
  Pll = static_cast<uint32_t>(Sws::Sws1)
};

constexpr auto kHPre = Flag<0xfu, 4u>{};
enum class HPre : uint32_t {
  HPre0 = kHPre.Make(0x1u),
  HPre1 = kHPre.Make(0x2u),
  HPre2 = kHPre.Make(0x4u),
  HPre3 = kHPre.Make(0x8u),
};
enum class HPreDiv : uint32_t {
  Div1   = 0x00000000u,
  Div2   = kHPre.Make(0x8u),
  Div4   = kHPre.Make(0x9u),
  Div8   = kHPre.Make(0xau),
  Div16  = kHPre.Make(0xbu),
  Div64  = kHPre.Make(0xcu),
  Div128 = kHPre.Make(0xdu),
  Div256 = kHPre.Make(0xeu),
  Div512 = kHPre.Make(0xfu),
};

constexpr auto kPPre = Flag<0x7u, 8u>{};
enum class PPre {
  Pre0 = kPPre.Make(0x01u),
  Pre1 = kPPre.Make(0x02u),
  Pre2 = kPPre.Make(0x04u),
};
enum class PPreDiv {
  Div1   = 0x00000000u,
  Div2   = Flag<0x1u, 10u>::value,
  Div4   = Flag<0x5u, 8u>::value,
  Div8   = Flag<0x3u, 9u>::value,
  Div16  = Flag<0x7u, 8u>::value
};

// TODO fix rcc file
using PPre1Div = PPreDiv;
using PPre2Div = int;
constexpr auto kPPre1 = kPPre;
constexpr auto kPPre2 = kPPre;

/*!< ADCPPRE configuration */
constexpr uint32_t kPllSrc = Flag<0x1u, 16u>::value;
enum class PllSrc : uint32_t {
  HsiDiv2   = 0x00000000u,
  HsePrediv = 0x00010000u
};

constexpr auto kPllMul = Flag<0xfu, 18u>{};
enum class PllMul : uint32_t {
PllMul_0 = kPllMul.Make(0x1u),  /*!< 0x00040000 */
PllMul_1 = kPllMul.Make(0x2u),  /*!< 0x00080000 */
PllMul_2 = kPllMul.Make(0x4u),  /*!< 0x00100000 */
PllMul_3 = kPllMul.Make(0x8u),  /*!< 0x00200000 */
PllMul2 =  (0x00000000U),                 /*!< PLL input clock*2 */
PllMul3 =  (0x00040000U),                 /*!< PLL input clock*3 */
PllMul4 =  (0x00080000U),                 /*!< PLL input clock*4 */
PllMul5 =  (0x000C0000U),                 /*!< PLL input clock*5 */
PllMul6 =  (0x00100000U),                 /*!< PLL input clock*6 */
PllMul7 =  (0x00140000U),                 /*!< PLL input clock*7 */
PllMul8 =  (0x00180000U),                 /*!< PLL input clock*8 */
PllMul9 =  (0x001C0000U),                 /*!< PLL input clock*9 */
PllMul10 = (0x00200000U),                 /*!< PLL input clock10 */
PllMul11 = (0x00240000U),                 /*!< PLL input clock*11 */
PllMul12 = (0x00280000U),                 /*!< PLL input clock*12 */
PllMul13 = (0x002C0000U),                 /*!< PLL input clock*13 */
PllMul14 = (0x00300000U),                 /*!< PLL input clock*14 */
PllMul15 = (0x00340000U),                 /*!< PLL input clock*15 */
PllMul16 = (0x00380000U)
};

}  // namespace cfgr

namespace cfgr2 {

constexpr uint32_t kPrediv = Flag<0xfu, 0u>::value;

}  // namespace cfgr2

constexpr auto kApb1Grp2PeriphSysCfg = RegisterValue<APB2ENR>{Flag<0x1u, 0u>::value};
constexpr auto kAhb1Grp1PeriphGpioA = RegisterValue<AHBENR>{Flag<0x1u, 17u>::value};
constexpr auto kAhb1Grp1PeriphGpioB = RegisterValue<AHBENR>{Flag<0x1u, 18u>::value};
constexpr auto kAhb1Grp1PeriphGpioC = RegisterValue<AHBENR>{Flag<0x1u, 19u>::value};

namespace cr {
constexpr uint32_t kHsiOn = Flag<0x1u, 0u>::value;
constexpr uint32_t kHsiRdy = Flag<0x1u, 1u>::value;
constexpr auto kHsiTrim = Flag<0x1fu, 3u>{};
enum class HsiTrim : uint32_t {
  HsiTrim0 = kHsiTrim.Make(0x01u),
  HsiTrim1 = kHsiTrim.Make(0x02u),
  HsiTrim2 = kHsiTrim.Make(0x04u),
  HsiTrim3 = kHsiTrim.Make(0x08u),
  HsiTrim4 = kHsiTrim.Make(0x10u)
};
constexpr auto kHsiCal = Flag<0xffu, 8u>{};
enum class HsiCal : uint32_t {
  HsiCal0 = kHsiCal.Make(0x01u),
  HsiCal1 = kHsiCal.Make(0x02u),
  HsiCal2 = kHsiCal.Make(0x04u),
  HsiCal3 = kHsiCal.Make(0x08u),
  HsiCal4 = kHsiCal.Make(0x10u),
  HsiCal5 = kHsiCal.Make(0x20u),
  HsiCal6 = kHsiCal.Make(0x40u),
  HsiCal7 = kHsiCal.Make(0x80u),
};
constexpr uint32_t kHseOn = Flag<0x1u, 16u>::value;
constexpr uint32_t kHseRdy = Flag<0x1u, 17u>::value;
constexpr uint32_t kHseByp = Flag<0x1u, 18u>::value;
constexpr uint32_t kCssOn = Flag<0x1u, 19u>::value;
constexpr uint32_t kPllOn = Flag<0x1u, 24u>::value;
constexpr uint32_t kPllRdy = Flag<0x1u, 25u>::value;
}

constexpr uint32_t kPllCfgrPllSrc = Flag<0x3u, 0u>::value;
constexpr uint32_t kPllCfgrPllM = Flag<0x7u, 4u>::value;
constexpr uint32_t kPllCfgrPllN = Flag<0x7fu, 8u>::value;
constexpr uint32_t kPllCfgrPllR = Flag<0x3u, 25u>::value;

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
