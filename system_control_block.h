#if !defined(SYSTEM_CONTROL_BLOCK)
#define SYSTEM_CONTROL_BLOCK

#include <cstdint>
#include <cstddef>
#include <type_traits>

static constexpr uint32_t kScsBaseAddress = 0xE000E000UL; // System Control Space Base Address
static constexpr uint32_t kScbBaseAddress = kScsBaseAddress + 0x0D00UL; // System Control Block Base Address

using RegByte = volatile uint8_t;
using Register = volatile uint32_t;
using ReadOnlyRegister = volatile uint32_t const;

class SystemControlBlock {
 public:
  ReadOnlyRegister CPUID;                  /*!< Offset: 0x000 (R/ )  CPUID Base Register */
  Register ICSR;                   /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register */
  Register VTOR;                   /*!< Offset: 0x008 (R/W)  Vector Table Offset Register */
  Register AIRCR;                  /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */
  Register SCR;                    /*!< Offset: 0x010 (R/W)  System Control Register */
  Register CCR;                    /*!< Offset: 0x014 (R/W)  Configuration Control Register */
  RegByte  SHP[12U];               /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
  Register SHCSR;                  /*!< Offset: 0x024 (R/W)  System Handler Control and State Register */
  Register CFSR;                   /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register */
  Register HFSR;                   /*!< Offset: 0x02C (R/W)  HardFault Status Register */
  Register DFSR;                   /*!< Offset: 0x030 (R/W)  Debug Fault Status Register */
  Register MMFAR;                  /*!< Offset: 0x034 (R/W)  MemManage Fault Address Register */
  Register BFAR;                   /*!< Offset: 0x038 (R/W)  BusFault Address Register */
  Register AFSR;                   /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register */
  ReadOnlyRegister PFR[2U];                /*!< Offset: 0x040 (R/ )  Processor Feature Register */
  ReadOnlyRegister DFR;                    /*!< Offset: 0x048 (R/ )  Debug Feature Register */
  ReadOnlyRegister ADR;                    /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register */
  ReadOnlyRegister MMFR[4U];               /*!< Offset: 0x050 (R/ )  Memory Model Feature Register */
  ReadOnlyRegister ISAR[5U];               /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register */
  uint32_t RESERVED0[5U];
  Register CPACR;                  /*!< Offset: 0x088 (R/W)  Coprocessor Access Control Register */
  void *operator new(size_t) {
    return reinterpret_cast<void*>(kScbBaseAddress);
  }
};

static_assert(std::is_standard_layout<SystemControlBlock>::value);

#endif
