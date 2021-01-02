#if !defined(SYSTEM_CONTROL_BLOCK)
#define SYSTEM_CONTROL_BLOCK

#include "addresses.h"
#include "device_register.h"
#include "module.h"

using ScbBaseAddress = std::integral_constant<uint32_t, address::scb::kBaseAddress>;

namespace scb {
 enum : uint32_t {
  CPUID,                  /*!< Offset: 0x000 (R/ )  CPUID Base Register */
  ICSR,                   /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register */
  RESERVED0,
  AIRCR,                  /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */
  SCR,                    /*!< Offset: 0x010 (R/W)  System Control Register */
  CCR,                    /*!< Offset: 0x014 (R/W)  Configuration Control Register */
  RESERVED1,
  SHP,                    /*!< Offset: 0x01C (R/W)  System Handlers Priority Registers. [0] is RESERVED */
  SHCSR                   /*!< Offset: 0x024 (R/W)  System Handler Control and State Register */
};
}  // namespace scb

using SystemControlBlock = Module<ScbBaseAddress,
ReadOnlyRegister,
Register,
uint32_t,
Register,
Register,
Register,
uint32_t,
Register[2u],
Register
>;

static_assert(std::is_standard_layout<SystemControlBlock>::value);

constexpr uint32_t kFlashBase = 0x08000000u;           /*!< FLASH(up to 512 KB) base address */
constexpr uint32_t kSramBase  = 0x20000000u;           /*!< SRAM1(up to 128 KB) base address */

constexpr auto kScbAircrVectKey = Flag<0xfffful, 16u>{};
constexpr auto kScbAircrPriGroup = Flag<7ul, 8u>{};

#endif
