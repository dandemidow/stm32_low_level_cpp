/**
  ******************************************************************************
  * @file    system_stm32l4xx.c
  * @author  MCD Application Team
  * @brief   CMSIS Cortex-M4 Device Peripheral Access Layer System Source File
  *
  *   This file provides two functions and one global variable to be called from
  *   user application:
  *      - SystemInit(): This function is called at startup just after reset and
  *                      before branch to main program. This call is made inside
  *                      the "startup_stm32l4xx.s" file.
  *
  *      - SystemCoreClock variable: Contains the core clock (HCLK), it can be used
  *                                  by the user application to setup the SysTick
  *                                  timer or configure other parameters.
  *
  *      - SystemCoreClockUpdate(): Updates the variable SystemCoreClock and must
  *                                 be called whenever the core clock is changed
  *                                 during program execution.
  *
  *   After each device reset the MSI (4 MHz) is used as system clock source.
  *   Then SystemInit() function is called, in "startup_stm32l4xx.s" file, to
  *   configure the system clock before to branch to main program.
  *
  *   This file configures the system clock as follows:
  *=============================================================================
  *-----------------------------------------------------------------------------
  *        System Clock source                    | MSI
  *-----------------------------------------------------------------------------
  *        SYSCLK(Hz)                             | 4000000
  *-----------------------------------------------------------------------------
  *        HCLK(Hz)                               | 4000000
  *-----------------------------------------------------------------------------
  *        AHB Prescaler                          | 1
  *-----------------------------------------------------------------------------
  *        APB1 Prescaler                         | 1
  *-----------------------------------------------------------------------------
  *        APB2 Prescaler                         | 1
  *-----------------------------------------------------------------------------
  *        PLL_M                                  | 1
  *-----------------------------------------------------------------------------
  *        PLL_N                                  | 8
  *-----------------------------------------------------------------------------
  *        PLL_P                                  | 7
  *-----------------------------------------------------------------------------
  *        PLL_Q                                  | 2
  *-----------------------------------------------------------------------------
  *        PLL_R                                  | 2
  *-----------------------------------------------------------------------------
  *        PLLSAI1_P                              | NA
  *-----------------------------------------------------------------------------
  *        PLLSAI1_Q                              | NA
  *-----------------------------------------------------------------------------
  *        PLLSAI1_R                              | NA
  *-----------------------------------------------------------------------------
  *        PLLSAI2_P                              | NA
  *-----------------------------------------------------------------------------
  *        PLLSAI2_Q                              | NA
  *-----------------------------------------------------------------------------
  *        PLLSAI2_R                              | NA
  *-----------------------------------------------------------------------------
  *        Require 48MHz for USB OTG FS,          | Disabled
  *        SDIO and RNG clock                     |
  *-----------------------------------------------------------------------------
  *=============================================================================
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

#include "frequency.h"
#include "register/reset_clock_control.h"

#if !defined  (HSE_VALUE)
constexpr auto kHseValue = 8_MHz;  // Value of the External oscillator
#endif /* HSE_VALUE */

#if !defined  (HSI_VALUE)
constexpr auto kHsiValue = 8_MHz; // Value of the Internal oscillator
#endif /* HSI_VALUE */

#if !defined (HSI48_VALUE)
constexpr auto kHsi48Value = 48_MHz;  // Default value of the HSI48 Internal oscillator in Hz.
#endif /* HSI48_VALUE */

/************************* Miscellaneous Configuration ************************/
/*!< Uncomment the following line if you need to relocate your vector Table in
     Internal SRAM. */
/* #define VECT_TAB_SRAM */
// Vector Table base offset field.
// This value must be a multiple of 0x200.
constexpr uint32_t kVectTabOffset = 0x00u;
/******************************************************************************/

  /* The SystemCoreClock variable is updated in three ways:
      1) by calling CMSIS function SystemCoreClockUpdate()
      2) by calling HAL API function HAL_RCC_GetHCLKFreq()
      3) each time HAL_RCC_ClockConfig() is called to configure the system clock frequency
         Note: If you use this function to configure the system clock; then there
               is no need to call the 2 first functions listed above, since SystemCoreClock
               variable is updated automatically.
  */
hertz SystemCoreClock = 8_MHz;

[[maybe_unused]] static constexpr uint8_t  APBPrescTable[8] =  {0U, 0U, 0U, 0U, 1U, 2U, 3U, 4U};

/**
  * @brief  Setup the microcontroller system.
  * @param  None
  * @retval None
  */

void SystemInitialization() {
    using namespace ll::rcc;
    auto &rcc = *new ResetClockControl {};

    /* Reset the RCC clock configuration to the default reset state ------------*/
    /* Set HSION bit */
    rcc.get<CR>() |= 0x00000001u;

    /* Reset SW[1:0], HPRE[3:0], PPRE[2:0], ADCPRE, MCOSEL[2:0], MCOPRE[2:0] and PLLNODIV bits */
    rcc.get<CR>() &= 0x08FFB80Cu;

    /* Reset HSEON, CSSON and PLLON bits */
    rcc.get<CR>() &= (uint32_t)0xFEF6FFFFU;

    /* Reset HSEBYP bit */
    rcc.get<CR>() &= (uint32_t)0xFFFBFFFFU;

    /* Reset PLLSRC, PLLXTPRE and PLLMUL[3:0] bits */
    rcc.get<CFGR>() &= (uint32_t)0xFFC0FFFFU;

    /* Reset PREDIV[3:0] bits */
    rcc.get<CFGR2>() &= (uint32_t)0xFFFFFFF0U;

    /* Reset USART1SW[1:0], I2C1SW and ADCSW bits */
    rcc.get<CFGR3>() &= (uint32_t)0xFFFFFEECU;

    /* Reset HSI14 bit */
    rcc.get<CR2>() &= (uint32_t)0xFFFFFFFEU;

    /* Disable all interrupts */
    rcc.set<CIR>(0x00000000U);
}

extern "C" {
void SystemInit(void) {
  SystemInitialization();
}

/**
  * @brief  Update SystemCoreClock variable according to Clock Register Values.
  *         The SystemCoreClock variable contains the core clock (HCLK), it can
  *         be used by the user application to setup the SysTick timer or configure
  *         other parameters.
  *
  * @note   Each time the core clock (HCLK) changes, this function must be called
  *         to update SystemCoreClock variable value. Otherwise, any configuration
  *         based on this variable will be incorrect.
  *
  * @note   - The system frequency computed by this function is not the real
  *           frequency in the chip. It is calculated based on the predefined
  *           constant and the selected clock source:
  *
  *           - If SYSCLK source is MSI, SystemCoreClock will contain the MSI_VALUE(*)
  *
  *           - If SYSCLK source is HSI, SystemCoreClock will contain the HSI_VALUE(**)
  *
  *           - If SYSCLK source is HSE, SystemCoreClock will contain the HSE_VALUE(***)
  *
  *           - If SYSCLK source is PLL, SystemCoreClock will contain the HSE_VALUE(***)
  *             or HSI_VALUE(*) or MSI_VALUE(*) multiplied/divided by the PLL factors.
  *
  *         (*) MSI_VALUE is a constant defined in stm32l4xx_hal.h file (default value
  *             4 MHz) but the real value may vary depending on the variations
  *             in voltage and temperature.
  *
  *         (**) HSI_VALUE is a constant defined in stm32l4xx_hal.h file (default value
  *              16 MHz) but the real value may vary depending on the variations
  *              in voltage and temperature.
  *
  *         (***) HSE_VALUE is a constant defined in stm32l4xx_hal.h file (default value
  *              8 MHz), user has to ensure that HSE_VALUE is same as the real
  *              frequency of the crystal used. Otherwise, this function may
  *              have wrong result.
  *
  *         - The result of this function could be not correct when using fractional
  *           value for HSE crystal.
  *
  * @param  None
  * @retval None
  */
void SystemCoreClockUpdate(void) {
//  constexpr std::array<uint8_t, 16u> AHBPrescTable {0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 1U, 2U, 3U, 4U, 6U, 7U, 8U, 9U};
  auto &rcc = *new ResetClockControl {};

//  /*MSI frequency range in HZ*/
//  auto msirange = GetMsiRangeFrequency();

//  /* Get SYSCLK source -------------------------------------------------------*/
//  SystemCoreClock = GetSysClkSource(msirange);

//  /* Compute HCLK clock frequency --------------------------------------------*/
//  /* Get HCLK prescaler */
//  uint32_t tmp = AHBPrescTable[(rcc.And<ll::rcc::CFGR>(ll::rcc::cfgr::kHPre) >> 4U)];
//  /* HCLK clock frequency */
//  SystemCoreClock = hertz{static_cast<uint32_t>(SystemCoreClock.count()) >> tmp};

  uint32_t pllmull = 0, pllsource = 0, predivfactor = 0;

  /* Get SYSCLK source -------------------------------------------------------*/
  uint32_t tmp = rcc.Get<CFGR>() & RCC_CFGR_SWS;

            switch (tmp)
            {
              case RCC_CFGR_SWS_HSI:  /* HSI used as system clock */
                SystemCoreClock = HSI_VALUE;
                break;
              case RCC_CFGR_SWS_HSE:  /* HSE used as system clock */
                SystemCoreClock = HSE_VALUE;
                break;
              case RCC_CFGR_SWS_PLL:  /* PLL used as system clock */
                /* Get PLL clock source and multiplication factor ----------------------*/
                pllmull = RCC->CFGR & RCC_CFGR_PLLMUL;
                pllsource = RCC->CFGR & RCC_CFGR_PLLSRC;
                pllmull = ( pllmull >> 18) + 2;
                predivfactor = (RCC->CFGR2 & RCC_CFGR2_PREDIV) + 1;

                if (pllsource == RCC_CFGR_PLLSRC_HSE_PREDIV)
                {
                  /* HSE used as PLL clock source : SystemCoreClock = HSE/PREDIV * PLLMUL */
                  SystemCoreClock = (HSE_VALUE/predivfactor) * pllmull;
                }
          #if defined(STM32F042x6) || defined(STM32F048xx) || defined(STM32F072xB) || defined(STM32F078xx) || defined(STM32F091xC) || defined(STM32F098xx)
                else if (pllsource == RCC_CFGR_PLLSRC_HSI48_PREDIV)
                {
                  /* HSI48 used as PLL clock source : SystemCoreClock = HSI48/PREDIV * PLLMUL */
                  SystemCoreClock = (HSI48_VALUE/predivfactor) * pllmull;
                }
          #endif /* STM32F042x6 || STM32F048xx || STM32F072xB || STM32F078xx || STM32F091xC || STM32F098xx */
                else
                {
          #if defined(STM32F042x6) || defined(STM32F048xx)  || defined(STM32F070x6) \
           || defined(STM32F078xx) || defined(STM32F071xB)  || defined(STM32F072xB) \
           || defined(STM32F070xB) || defined(STM32F091xC) || defined(STM32F098xx)  || defined(STM32F030xC)
                  /* HSI used as PLL clock source : SystemCoreClock = HSI/PREDIV * PLLMUL */
                  SystemCoreClock = (HSI_VALUE/predivfactor) * pllmull;
          #else
                  /* HSI used as PLL clock source : SystemCoreClock = HSI/2 * PLLMUL */
                  SystemCoreClock = (HSI_VALUE >> 1) * pllmull;
          #endif /* STM32F042x6 || STM32F048xx || STM32F070x6 ||
                    STM32F071xB || STM32F072xB || STM32F078xx || STM32F070xB ||
                    STM32F091xC || STM32F098xx || STM32F030xC */
                }
                break;
              default: /* HSI used as system clock */
                SystemCoreClock = HSI_VALUE;
                break;
            }
            /* Compute HCLK clock frequency ----------------*/
            /* Get HCLK prescaler */
            tmp = AHBPrescTable[((RCC->CFGR & RCC_CFGR_HPRE) >> 4)];
            /* HCLK clock frequency */
            SystemCoreClock >>= tmp;
          }
} // extern "C"
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
