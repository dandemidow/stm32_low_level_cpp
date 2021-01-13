/**
  */

#include <array>
#include <cstdint>
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
void SVC_Handler() __attribute_default__;
void PendSV_Handler() __attribute_default__;
void SysTick_Handler() __attribute_default__;
void WWDG_IRQHandler() __attribute_default__;
void RTC_IRQHandler() __attribute_default__;
void FLASH_IRQHandler() __attribute_default__;
void RCC_IRQHandler() __attribute_default__;
void EXTI0_1_IRQHandler() __attribute_default__;
void EXTI2_3_IRQHandler() __attribute_default__;
void EXTI4_15_IRQHandler() __attribute_default__;
void DMA1_Channel1_IRQHandler() __attribute_default__;
void DMA1_Channel2_3_IRQHandler() __attribute_default__;
void DMA1_Channel4_5_IRQHandler() __attribute_default__;
void ADC1_IRQHandler() __attribute_default__;
void TIM1_BRK_TIM15_IRQHandler() __attribute_default__;
void TIM1_CC_IRQHandler() __attribute_default__;
void TIM2_IRQHandler() __attribute_default__;
void TIM3_IRQHandler() __attribute_default__;
void TIM6_IRQHandler() __attribute_default__;
void TIM14_IRQHandler() __attribute_default__;
void TIM15_IRQHandler() __attribute_default__;
void TIM16_IRQHandler() __attribute_default__;
void TIM17_IRQHandler() __attribute_default__;
void I2C1_IRQHandler() __attribute_default__;
void I2C2_IRQHandler() __attribute_default__;
void SPI1_IRQHandler() __attribute_default__;
void SPI2_IRQHandler() __attribute_default__;
void USART1_IRQHandler() __attribute_default__;
void USART2_IRQHandler() __attribute_default__;

union IrqElement {
  Handler handler;
  uint32_t *address;
};

std::array<IrqElement, 48> vector __attribute__((section (".isr_vector"))) {{
    {.address = &_estack},
    {&Reset_Handler},
    {&NMI_Handler},
    {&HardFault_Handler},
    {nullptr},
    {nullptr},
    {nullptr},
    {nullptr},
    {nullptr},
    {nullptr},
    {nullptr},
    {&SVC_Handler},
    {nullptr},
    {nullptr},
    {&PendSV_Handler},
    {&SysTick_Handler},
    {&WWDG_IRQHandler},
    {nullptr},
    {&RTC_IRQHandler},
    {&FLASH_IRQHandler},
    {&RCC_IRQHandler},
    {&EXTI0_1_IRQHandler},
    {&EXTI2_3_IRQHandler},
    {&EXTI4_15_IRQHandler},
    {nullptr},
    {&DMA1_Channel1_IRQHandler},
    {&DMA1_Channel2_3_IRQHandler},
    {&DMA1_Channel4_5_IRQHandler},
    {&ADC1_IRQHandler},
    {&TIM1_BRK_TIM15_IRQHandler},
    {&TIM1_CC_IRQHandler},
    {nullptr},
    {&TIM3_IRQHandler},
    {&TIM6_IRQHandler},
    {nullptr},
    {&TIM14_IRQHandler},
    {&TIM15_IRQHandler},
    {&TIM16_IRQHandler},
    {&TIM17_IRQHandler},
    {&I2C1_IRQHandler},
    {&I2C2_IRQHandler},
    {&SPI1_IRQHandler},
    {&SPI2_IRQHandler},
    {&USART1_IRQHandler},
    {&USART2_IRQHandler},
    {nullptr},
    {nullptr},
    {nullptr}
}};
