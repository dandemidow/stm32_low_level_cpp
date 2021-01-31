/**
  */

#include <array>
#include <cstdint>
#include <cstring>

extern void main [[ noreturn ]] ();
extern void SystemInit();

extern "C" {
extern void __libc_init_array(void);
extern uint32_t _estack;
extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;
}  // extern "C"

[[noreturn]] void Reset_Handler() {
  SystemInit();
  auto data_size = static_cast<size_t>(&_edata - &_sdata);
  if (data_size) {
    std::memcpy(&_sdata, &_sidata, data_size);
  }
  auto bss_size = static_cast<size_t>(&_ebss - &_sbss);
  if (bss_size) {
    std::memset(&_sbss, 0x00, bss_size);
  }
  __libc_init_array();
  main();
}

[[noreturn]] void Default_Handler() {
  while(true) {}
}

using Handler = void(*)();
#define __attribute_default__ __attribute__((noreturn, nothrow, weak, alias("_Z15Default_Handlerv")))

void NMI_Handler() __attribute_default__;
void HardFault_Handler() __attribute_default__;
void MemManage_Handler() __attribute_default__;
void BusFault_Handler() __attribute_default__;
void UsageFault_Handler() __attribute_default__;
void SVC_Handler() __attribute_default__;
void DebugMon_Handler() __attribute_default__;
void PendSV_Handler() __attribute_default__;
void SysTick_Handler() __attribute_default__;
void WWDG_IRQHandler() __attribute_default__;
void PVD_PVM_IRQHandler() __attribute_default__;
void TAMP_STAMP_IRQHandler() __attribute_default__;
void RTC_WKUP_IRQHandler() __attribute_default__;
void FLASH_IRQHandler() __attribute_default__;
void RCC_IRQHandler() __attribute_default__;
void EXTI0_IRQHandler() __attribute_default__;
void EXTI1_IRQHandler() __attribute_default__;
void EXTI2_IRQHandler() __attribute_default__;
void EXTI3_IRQHandler() __attribute_default__;
void EXTI4_IRQHandler() __attribute_default__;
void DMA1_Channel1_IRQHandler() __attribute_default__;
void DMA1_Channel2_IRQHandler() __attribute_default__;
void DMA1_Channel3_IRQHandler() __attribute_default__;
void DMA1_Channel4_IRQHandler() __attribute_default__;
void DMA1_Channel5_IRQHandler() __attribute_default__;
void DMA1_Channel6_IRQHandler() __attribute_default__;
void DMA1_Channel7_IRQHandler() __attribute_default__;
void ADC1_IRQHandler() __attribute_default__;
void CAN1_TX_IRQHandler() __attribute_default__;
void CAN1_RX0_IRQHandler() __attribute_default__;
void CAN1_RX1_IRQHandler() __attribute_default__;
void CAN1_SCE_IRQHandler() __attribute_default__;
void EXTI9_5_IRQHandler() __attribute_default__;
void TIM1_BRK_TIM15_IRQHandler() __attribute_default__;
void TIM1_UP_TIM16_IRQHandler() __attribute_default__;
void TIM1_TRG_COM_IRQHandler() __attribute_default__;
void TIM1_CC_IRQHandler() __attribute_default__;
void TIM2_IRQHandler() __attribute_default__;
void TIM3_IRQHandler() __attribute_default__;
void I2C1_EV_IRQHandler() __attribute_default__;
void I2C1_ER_IRQHandler() __attribute_default__;
void I2C2_EV_IRQHandler() __attribute_default__;
void I2C2_ER_IRQHandler() __attribute_default__;
void SPI1_IRQHandler() __attribute_default__;
void SPI2_IRQHandler() __attribute_default__;
void USART1_IRQHandler() __attribute_default__;
void USART2_IRQHandler() __attribute_default__;
void USART3_IRQHandler() __attribute_default__;
void EXTI15_10_IRQHandler() __attribute_default__;
void RTC_Alarm_IRQHandler() __attribute_default__;
void SDMMC1_IRQHandler() __attribute_default__;
void SPI3_IRQHandler() __attribute_default__;
void UART4_IRQHandler() __attribute_default__;
void TIM6_DAC_IRQHandler() __attribute_default__;
void DMA2_Channel1_IRQHandler() __attribute_default__;
void DMA2_Channel2_IRQHandler() __attribute_default__;
void DMA2_Channel3_IRQHandler() __attribute_default__;
void DMA2_Channel4_IRQHandler() __attribute_default__;
void DMA2_Channel5_IRQHandler() __attribute_default__;
void DFSDM1_FLT0_IRQHandler() __attribute_default__;
void DFSDM1_FLT1_IRQHandler() __attribute_default__;
void COMP_IRQHandler() __attribute_default__;
void LPTIM1_IRQHandler() __attribute_default__;
void LPTIM2_IRQHandler() __attribute_default__;
void USB_IRQHandler() __attribute_default__;
void DMA2_Channel6_IRQHandler() __attribute_default__;
void DMA2_Channel7_IRQHandler() __attribute_default__;
void LPUART1_IRQHandler() __attribute_default__;
void QUADSPI_IRQHandler() __attribute_default__;
void I2C3_EV_IRQHandler() __attribute_default__;
void I2C3_ER_IRQHandler() __attribute_default__;
void SAI1_IRQHandler() __attribute_default__;
void TSC_IRQHandler() __attribute_default__;
void RNG_IRQHandler() __attribute_default__;
void FPU_IRQHandler() __attribute_default__;
void CRS_IRQHandler() __attribute_default__;
void I2C4_EV_IRQHandler() __attribute_default__;
void I2C4_ER_IRQHandler() __attribute_default__;


union IrqElement {
  Handler handler;
  uint32_t *address;
};

std::array<IrqElement, 101> vector __attribute__((section (".isr_vector"))) {{
    {.address = &_estack},
    {&Reset_Handler},
    {&NMI_Handler},
    {&HardFault_Handler},
    {&MemManage_Handler},
    {&BusFault_Handler},
    {&UsageFault_Handler},
    {nullptr},
    {nullptr},
    {nullptr},
    {nullptr},
    {&SVC_Handler},
    {&DebugMon_Handler},
    {nullptr},
    {&PendSV_Handler},
    {&SysTick_Handler},
    {&WWDG_IRQHandler},
    {&PVD_PVM_IRQHandler},
    {&TAMP_STAMP_IRQHandler},
    {&RTC_WKUP_IRQHandler},
    {&FLASH_IRQHandler},
    {&RCC_IRQHandler},
    {&EXTI0_IRQHandler},
    {&EXTI1_IRQHandler},
    {&EXTI2_IRQHandler},
    {&EXTI3_IRQHandler},
    {&EXTI4_IRQHandler},
    {&DMA1_Channel1_IRQHandler},
    {&DMA1_Channel2_IRQHandler},
    {&DMA1_Channel3_IRQHandler},
    {&DMA1_Channel4_IRQHandler},
    {&DMA1_Channel5_IRQHandler},
    {&DMA1_Channel6_IRQHandler},
    {&DMA1_Channel7_IRQHandler},
    {&ADC1_IRQHandler},
    {&CAN1_TX_IRQHandler},
    {&CAN1_RX0_IRQHandler},
    {&CAN1_RX1_IRQHandler},
    {&CAN1_SCE_IRQHandler},
    {&EXTI9_5_IRQHandler},
    {&TIM1_BRK_TIM15_IRQHandler},
    {&TIM1_UP_TIM16_IRQHandler},
    {&TIM1_TRG_COM_IRQHandler},
    {&TIM1_CC_IRQHandler},
    {&TIM2_IRQHandler},
    {&TIM3_IRQHandler},
    {nullptr},
    {&I2C1_EV_IRQHandler},
    {&I2C1_ER_IRQHandler},
    {&I2C2_EV_IRQHandler},
    {&I2C2_ER_IRQHandler},
    {&SPI1_IRQHandler},
    {&SPI2_IRQHandler},
    {&USART1_IRQHandler},
    {&USART2_IRQHandler},
    {&USART3_IRQHandler},
    {&EXTI15_10_IRQHandler},
    {&RTC_Alarm_IRQHandler},
    {nullptr},
    {nullptr},
    {nullptr},
    {nullptr},
    {nullptr},
    {nullptr},
    {nullptr},
    {&SDMMC1_IRQHandler},
    {nullptr},
    {&SPI3_IRQHandler},
    {&UART4_IRQHandler},
    {nullptr},
    {&TIM6_DAC_IRQHandler},
    {nullptr},
    {&DMA2_Channel1_IRQHandler},
    {&DMA2_Channel2_IRQHandler},
    {&DMA2_Channel3_IRQHandler},
    {&DMA2_Channel4_IRQHandler},
    {&DMA2_Channel5_IRQHandler},
    {&DFSDM1_FLT0_IRQHandler},
    {&DFSDM1_FLT1_IRQHandler},
    {nullptr},
    {&COMP_IRQHandler},
    {&LPTIM1_IRQHandler},
    {&LPTIM2_IRQHandler},
    {&USB_IRQHandler},
    {&DMA2_Channel6_IRQHandler},
    {&DMA2_Channel7_IRQHandler},
    {&LPUART1_IRQHandler},
    {&QUADSPI_IRQHandler},
    {&I2C3_EV_IRQHandler},
    {&I2C3_ER_IRQHandler},
    {&SAI1_IRQHandler},
    {nullptr},
    {nullptr},
    {&TSC_IRQHandler},
    {nullptr},
    {nullptr},
    {&RNG_IRQHandler},
    {&FPU_IRQHandler},
    {&CRS_IRQHandler},
    {&I2C4_EV_IRQHandler},
    {&I2C4_ER_IRQHandler}
}};
