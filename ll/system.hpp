#if !defined(LL_SYSTEM_H_)
#define LL_SYSTEM_H_

#include "register/flash.hpp"

namespace ll {
namespace flash {
using namespace address::flash;

static inline void set_latency(AcrLatency latency) {
  auto &flash = *new Flash{};
  reg::modify(flash.get<flash::ACR>(), kAcrLatency, static_cast<uint32_t>(latency));
}

static inline AcrLatency get_latency() {
  auto &flash = *new Flash{};
  auto latency = bit::read(flash.get<flash::ACR>(), kAcrLatency);
  return static_cast<flash::AcrLatency>(latency);
}

}  // namespace flash
}  // namespace ll

#endif
