#if !defined(LL_SYSTEM_H_)
#define LL_SYSTEM_H_

#include "device_register.h"
#include "flash.hpp"

namespace ll {

static inline void flash_set_latency(uint32_t latency) {
  auto &flash = *new Flash{};
  reg::modify(flash.get<flash::ACR>(), address::flash::kAcrLatency, latency);
}

static inline uint32_t flash_get_latency() {
  auto &flash = *new Flash{};
  return bit::read(flash.get<flash::ACR>(), address::flash::kAcrLatency);
}

static constexpr uint32_t kFlashAcrLatency0 = 0x00000000u;
static constexpr uint32_t kFlashAcrLatency1 = 0x00000001u;
static constexpr uint32_t kFlashAcrLatency2 = 0x00000002u;
static constexpr uint32_t kFlashAcrLatency3 = 0x00000003u;
static constexpr uint32_t kFlashAcrLatency4 = 0x00000004u;

}  // namespace ll

#endif
