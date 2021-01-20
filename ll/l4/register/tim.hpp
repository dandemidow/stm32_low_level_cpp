#if !defined(TIM_HPP_)
#define TIM_HPP_

#include "addresses.h"
#include "device_register.h"
#include "module.h"

namespace ll::tim {
enum class index : uint32_t {
  T1 = address::tim::kT1,
  T3 = address::tim::kT3
};

namespace cr1 {

constexpr auto kCen = Flag<0x1u, 0u>{};
constexpr auto kUdis = Flag<0x1u, 1u>{};
constexpr auto kUrs = Flag<0x1u, 2u>{};
constexpr auto kOpm = Flag<0x1u, 3u>{};
constexpr auto kDir = Flag<0x1u, 4u>{};
constexpr auto kCms = Flag<0x3u, 5u>{};
constexpr auto kArpe = Flag<0x1u, 7u>{};
constexpr auto kCkd = Flag<0x3u, 8u>{};

}  // namespace cr1

namespace cr2 {

constexpr auto kCcpc = Flag<0x1u, 0u>{};
constexpr auto kCcus = Flag<0x1u, 2u>{};
constexpr auto kCcds = Flag<0x1u, 3u>{};
constexpr auto kMms = Flag<0x7u, 4u>{};
constexpr auto kTi1S = Flag<0x1u, 7u>{};
constexpr auto kOis1 = Flag<0x1u, 8u>{};
constexpr auto kOis1N = Flag<0x1u, 9u>{};
constexpr auto kOis2 = Flag<0x1u, 10u>{};
constexpr auto kOis2N = Flag<0x1u, 11u>{};
constexpr auto kOis3 = Flag<0x1u, 12u>{};
constexpr auto kOis3N = Flag<0x1u, 13u>{};
constexpr auto kOis4 = Flag<0x1u, 14u>{};

}  // namespace cr2

namespace smcr {

constexpr auto kSms = Flag<0x7u, 0u>{};
constexpr auto kOccs = Flag<0x1u, 3u>{};
constexpr auto kTs = Flag<0x7u, 4u>{};
constexpr auto kMsm = Flag<0x1u, 7u>{};
constexpr auto kEtf = Flag<0xfu, 8u>{};
constexpr auto kEtps = Flag<0x3u, 12u>{};
constexpr auto kEce = Flag<0x1u, 14u>{};
constexpr auto kEtp = Flag<0x1u, 15u>{};

}  // namespace smcr

namespace dier {

constexpr auto kUie = Flag<0x1u, 0u>{};
constexpr auto kCc1Ie = Flag<0x1u, 1u>{};
constexpr auto kCc2Ie = Flag<0x1u, 2u>{};
constexpr auto kCc3Ie = Flag<0x1u, 3u>{};
constexpr auto kCc4Ie = Flag<0x1u, 4u>{};
constexpr auto kComIe = Flag<0x1u, 5u>{};
constexpr auto kTie = Flag<0x1u, 6u>{};
constexpr auto kBie = Flag<0x1u, 7u>{};
constexpr auto kUde = Flag<0x1u, 8u>{};
constexpr auto kCc1De = Flag<0x1u, 9u>{};
constexpr auto kCc2De = Flag<0x1u, 10u>{};
constexpr auto kCc3De = Flag<0x1u, 11u>{};
constexpr auto kCc4De = Flag<0x1u, 12u>{};
constexpr auto kComDe = Flag<0x1u, 13u>{};
constexpr auto kTde = Flag<0x1u, 14u>{};

}  // namespace dier


namespace sr {

constexpr auto kUif = Flag<0x1u, 0u>{};
constexpr auto kCc1If = Flag<0x1u, 1u>{};
constexpr auto kCc2If = Flag<0x1u, 2u>{};
constexpr auto kCc3If = Flag<0x1u, 3u>{};
constexpr auto kCc4If = Flag<0x1u, 4u>{};
constexpr auto kComIf = Flag<0x1u, 5u>{};
constexpr auto kTif = Flag<0x1u, 6u>{};
constexpr auto kBif = Flag<0x1u, 7u>{};
constexpr auto kUde = Flag<0x1u, 8u>{};
constexpr auto kCc1Of = Flag<0x1u, 9u>{};
constexpr auto kCc2Of = Flag<0x1u, 10u>{};
constexpr auto kCc3Of = Flag<0x1u, 11u>{};
constexpr auto kCc4Of = Flag<0x1u, 12u>{};

}  // namspace sr

namespace egr {

constexpr auto kUg = Flag<0x1, 0u>{};
constexpr auto kCc1G = Flag<0x1u, 1u>{};
constexpr auto kCc2G = Flag<0x1u, 2u>{};
constexpr auto kCc3G = Flag<0x1u, 3u>{};
constexpr auto kCc4G = Flag<0x1u, 4u>{};
constexpr auto kComG = Flag<0x1u, 5u>{};
constexpr auto kTg = Flag<0x1u, 6u>{};
constexpr auto kBg = Flag<0x1u, 7u>{};

}  // namespace egr

enum : uint32_t {
  CR1,
  CR2,
  SMCR,
  DIER,
  SR,
  EGR,
  CCMR1,
  CCMR2,
  CCER,
  CNT,
  PSC,
  ARR,
  RCR,
  CCR1,
  CCR2,
  CCR3,
  CCR4,
  BDTR,
  DCR,
  DMAR,
  OR
};

}  // namespace ll::tim

using Tim = Module<ll::tim::index,
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
Register,
Register,
Register,
Register,
Register,
Register,
Register,
Register
>;

static_assert(std::is_standard_layout<Tim>::value);

#endif
