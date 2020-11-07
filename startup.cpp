/**
  */

#include <array>
#include <cstring>

extern int main ();

extern "C" {
extern void SystemInit(void);
extern void __libc_init_array(void);
extern uint32_t _estack;
extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;
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
  while(true) {}
}
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
  uint32_t *address;
  Handler handler;
};

std::array<IrqElement, 101> vector __attribute__((section (".isr_vector"))) {
    IrqElement{.address = &_estack},
    IrqElement{.handler = &Reset_Handler},
    IrqElement{.handler = &NMI_Handler},
    IrqElement{.handler = &HardFault_Handler},
    IrqElement{.handler = &MemManage_Handler},
    IrqElement{.handler = &BusFault_Handler},
    IrqElement{.handler = &UsageFault_Handler},
    IrqElement{.handler = nullptr},
    IrqElement{.handler = nullptr},
    IrqElement{.handler = nullptr},
    IrqElement{.handler = nullptr},
    IrqElement{.handler = &SVC_Handler},
    IrqElement{.handler = &DebugMon_Handler},
    IrqElement{.handler = nullptr},
    IrqElement{.handler = &PendSV_Handler},
    IrqElement{.handler = &SysTick_Handler},
    IrqElement{.handler = &WWDG_IRQHandler},
    IrqElement{.handler = &PVD_PVM_IRQHandler},
    IrqElement{.handler = &TAMP_STAMP_IRQHandler},
    IrqElement{.handler = &RTC_WKUP_IRQHandler},
    IrqElement{.handler = &FLASH_IRQHandler},
    IrqElement{.handler = &RCC_IRQHandler},
    IrqElement{.handler = &EXTI0_IRQHandler},
    IrqElement{.handler = &EXTI1_IRQHandler},
    IrqElement{.handler = &EXTI2_IRQHandler},
    IrqElement{.handler = &EXTI3_IRQHandler},
    IrqElement{.handler = &EXTI4_IRQHandler},
    IrqElement{.handler = &DMA1_Channel1_IRQHandler},
    IrqElement{.handler = &DMA1_Channel2_IRQHandler},
    IrqElement{.handler = &DMA1_Channel3_IRQHandler},
    IrqElement{.handler = &DMA1_Channel4_IRQHandler},
    IrqElement{.handler = &DMA1_Channel5_IRQHandler},
    IrqElement{.handler = &DMA1_Channel6_IRQHandler},
    IrqElement{.handler = &DMA1_Channel7_IRQHandler},
    IrqElement{.handler = &ADC1_IRQHandler},
    IrqElement{.handler = &CAN1_TX_IRQHandler},
    IrqElement{.handler = &CAN1_RX0_IRQHandler},
    IrqElement{.handler = &CAN1_RX1_IRQHandler},
    IrqElement{.handler = &CAN1_SCE_IRQHandler},
    IrqElement{.handler = &EXTI9_5_IRQHandler},
    IrqElement{.handler = &TIM1_BRK_TIM15_IRQHandler},
    IrqElement{.handler = &TIM1_UP_TIM16_IRQHandler},
    IrqElement{.handler = &TIM1_TRG_COM_IRQHandler},
    IrqElement{.handler = &TIM1_CC_IRQHandler},
    IrqElement{.handler = &TIM2_IRQHandler},
    IrqElement{.handler = &TIM3_IRQHandler},
    IrqElement{.handler = nullptr},
    IrqElement{.handler = &I2C1_EV_IRQHandler},
    IrqElement{.handler = &I2C1_ER_IRQHandler},
    IrqElement{.handler = &I2C2_EV_IRQHandler},
    IrqElement{.handler = &I2C2_ER_IRQHandler},
    IrqElement{.handler = &SPI1_IRQHandler},
    IrqElement{.handler = &SPI2_IRQHandler},
    IrqElement{.handler = &USART1_IRQHandler},
    IrqElement{.handler = &USART2_IRQHandler},
    IrqElement{.handler = &USART3_IRQHandler},
    IrqElement{.handler = &EXTI15_10_IRQHandler},
    IrqElement{.handler = &RTC_Alarm_IRQHandler},
    IrqElement{.handler = nullptr},
    IrqElement{.handler = nullptr},
    IrqElement{.handler = nullptr},
    IrqElement{.handler = nullptr},
    IrqElement{.handler = nullptr},
    IrqElement{.handler = nullptr},
    IrqElement{.handler = nullptr},
    IrqElement{.handler = &SDMMC1_IRQHandler},
    IrqElement{.handler = nullptr},
    IrqElement{.handler = &SPI3_IRQHandler},
    IrqElement{.handler = &UART4_IRQHandler},
    IrqElement{.handler = nullptr},
    IrqElement{.handler = &TIM6_DAC_IRQHandler},
    IrqElement{.handler = nullptr},
    IrqElement{.handler = &DMA2_Channel1_IRQHandler},
    IrqElement{.handler = &DMA2_Channel2_IRQHandler},
    IrqElement{.handler = &DMA2_Channel3_IRQHandler},
    IrqElement{.handler = &DMA2_Channel4_IRQHandler},
    IrqElement{.handler = &DMA2_Channel5_IRQHandler},
    IrqElement{.handler = &DFSDM1_FLT0_IRQHandler},
    IrqElement{.handler = &DFSDM1_FLT1_IRQHandler},
    IrqElement{.handler = nullptr},
    IrqElement{.handler = &COMP_IRQHandler},
    IrqElement{.handler = &LPTIM1_IRQHandler},
    IrqElement{.handler = &LPTIM2_IRQHandler},
    IrqElement{.handler = &USB_IRQHandler},
    IrqElement{.handler = &DMA2_Channel6_IRQHandler},
    IrqElement{.handler = &DMA2_Channel7_IRQHandler},
    IrqElement{.handler = &LPUART1_IRQHandler},
    IrqElement{.handler = &QUADSPI_IRQHandler},
    IrqElement{.handler = &I2C3_EV_IRQHandler},
    IrqElement{.handler = &I2C3_ER_IRQHandler},
    IrqElement{.handler = &SAI1_IRQHandler},
    IrqElement{.handler = nullptr},
    IrqElement{.handler = nullptr},
    IrqElement{.handler = &TSC_IRQHandler},
    IrqElement{.handler = nullptr},
    IrqElement{.handler = nullptr},
    IrqElement{.handler = &RNG_IRQHandler},
    IrqElement{.handler = &FPU_IRQHandler},
    IrqElement{.handler = &CRS_IRQHandler},
    IrqElement{.handler = &I2C4_EV_IRQHandler},
    IrqElement{.handler = &I2C4_ER_IRQHandler}
};
