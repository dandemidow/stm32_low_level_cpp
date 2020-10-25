#if !defined(SYSTEM_CONTROL_BLOCK)
#define SYSTEM_CONTROL_BLOCK

#include "device_register.h"
#include "module.h"

static constexpr uint32_t kScsBaseAddress = 0xE000E000UL; // System Control Space Base Address
static constexpr uint32_t kScbBaseAddress = kScsBaseAddress + 0x0D00UL; // System Control Block Base Address

namespace scb {
 enum : uint32_t {
  CPUID,                  /*!< Offset: 0x000 (R/ )  CPUID Base Register */
  ICSR,                   /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register */
  VTOR,                   /*!< Offset: 0x008 (R/W)  Vector Table Offset Register */
  AIRCR,                  /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */
  SCR,                    /*!< Offset: 0x010 (R/W)  System Control Register */
  CCR,                    /*!< Offset: 0x014 (R/W)  Configuration Control Register */
  SHP,                    /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
  SHCSR,                  /*!< Offset: 0x024 (R/W)  System Handler Control and State Register */
  CFSR,                   /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register */
  HFSR,                   /*!< Offset: 0x02C (R/W)  HardFault Status Register */
  DFSR,                   /*!< Offset: 0x030 (R/W)  Debug Fault Status Register */
  MMFAR,                  /*!< Offset: 0x034 (R/W)  MemManage Fault Address Register */
  BFAR,                   /*!< Offset: 0x038 (R/W)  BusFault Address Register */
  AFSR,                   /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register */
  PFR,                    /*!< Offset: 0x040 (R/ )  Processor Feature Register */
  DFR,                    /*!< Offset: 0x048 (R/ )  Debug Feature Register */
  ADR,                    /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register */
  MMFR,                   /*!< Offset: 0x050 (R/ )  Memory Model Feature Register */
  ISAR,                   /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register */
  RESERVED0,
  CPACR,                  /*!< Offset: 0x088 (R/W)  Coprocessor Access Control Register */
};
}  // namespace scb

using SystemControlBlock = Module<kScbBaseAddress,
ReadOnlyRegister,
Register,
Register,
Register,
Register,
Register,
RegByte[12u],
Register,
Register,
Register,
Register,
Register,
Register,
Register,
ReadOnlyRegister[2],
ReadOnlyRegister,
ReadOnlyRegister,
ReadOnlyRegister[4u],
ReadOnlyRegister[5u],
uint32_t[5U],
Register
>;

static_assert(std::is_standard_layout<SystemControlBlock>::value);

constexpr uint32_t kFlashBase = 0x08000000u;           /*!< FLASH(up to 512 KB) base address */
constexpr uint32_t kSramBase  = 0x20000000u;           /*!< SRAM1(up to 128 KB) base address */

#endif
