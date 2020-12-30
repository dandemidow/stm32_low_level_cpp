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
#include "register/system_control_block.h"

#if !defined  (HSE_VALUE)
constexpr auto kHseValue = 8_MHz;  // Value of the External oscillator
#endif /* HSE_VALUE */

#if !defined  (MSI_VALUE)
constexpr auto kMsiValue = 4_MHz;  // Value of the Internal oscillator
#endif /* MSI_VALUE */

#if !defined  (HSI_VALUE)
constexpr auto kHsiValue = 16_MHz; // Value of the Internal oscillator
#endif /* HSI_VALUE */

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
hertz SystemCoreClock = 4_MHz;

[[maybe_unused]] static constexpr uint8_t  APBPrescTable[8] =  {0U, 0U, 0U, 0U, 1U, 2U, 3U, 4U};

hertz GetMsiRangeFrequency() {
  using namespace ll::rcc;
  constexpr std::array<hertz, 12u> MSIRangeTable {100_KHz,
                                                  200_KHz,
                                                  400_KHz,
                                                  800_KHz,
                                                  1_MHz,
                                                  2_MHz,
                                                  4_MHz,
                                                  8_MHz,
                                                  16_MHz,
                                                  24_MHz,
                                                  32_MHz,
                                                  48_MHz};
  uint32_t msirange;
  auto &rcc = *new ResetClockControl {};
  /* Get MSI Range frequency--------------------------------------------------*/
  if(rcc.And<CR>(kCrMsiRgSel) == bit::RESET) { /* MSISRANGE from RCC_CSR applies */
    msirange = rcc.And<CSR>(kCsrMsiSRange) >> 8U;
  } else { /* MSIRANGE from RCC_CR applies */
    msirange = rcc.And<CR>(kCrMsiRange.value) >> 4U;
  }
  /*MSI frequency range in HZ*/
  return MSIRangeTable[msirange];
}

hertz GetSysClkSource(hertz msirange) {
  using namespace ll::rcc;
  hertz result {};
  uint32_t pllm = 2u;
  uint32_t pllvco = 0u;
  uint32_t pllr = 2u;

  auto &rcc = *new ResetClockControl {};
  switch (rcc.And<CFGR>(cfgr::kSws)) {
    case 0x00:  /* MSI used as system clock source */
      result = msirange;
      break;

    case 0x04:  /* HSI used as system clock source */
      result = kHsiValue;
      break;

    case 0x08:  /* HSE used as system clock source */
      result = kHseValue;
      break;

    case 0x0C:  /* PLL used as system clock  source */
      /* PLL_VCO = (HSE_VALUE or HSI_VALUE or MSI_VALUE/ PLLM) * PLLN
         SYSCLK = PLL_VCO / PLLR
         */
      pllm = (rcc.And<PLLCFGR>(kPllCfgrPllM) >> 4U) + 1U ;

      switch (rcc.And<PLLCFGR>(kPllCfgrPllSrc)) {
        case 0x02:  /* HSI used as PLL clock source */
          pllvco = hertz{kHsiValue / pllm}.count();
          break;

        case 0x03:  /* HSE used as PLL clock source */
          pllvco = hertz{kHseValue / pllm}.count();
          break;

        default:    /* MSI used as PLL clock source */
          pllvco = (msirange / pllm).count();
          break;
      }
      pllvco = pllvco * (rcc.And<PLLCFGR>(kPllCfgrPllN) >> 8U);
      pllr = ((rcc.And<PLLCFGR>(kPllCfgrPllR) >> 25U) + 1U) * 2U;
      result = hertz{pllvco/pllr};
      break;

    default:
      result = hertz{msirange};
      break;
  }
  return result;
}

/**
  * @brief  Setup the microcontroller system.
  * @param  None
  * @retval None
  */

void SystemInitialization() {
    using namespace ll::rcc;
    auto &rcc = *new ResetClockControl {};
    auto &scb = *new SystemControlBlock {};
    /* FPU settings ------------------------------------------------------------*/
    #if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
      scb.get<scb::CPACR>() |= ((3UL << 10*2)|(3UL << 11*2));  /* set CP10 and CP11 Full Access */
    #endif

    /* Reset the RCC clock configuration to the default reset state ------------*/
    /* Set MSION bit */
    rcc.get<CR>() |= kCrMsiOn;

    /* Reset CFGR register */
    rcc.set<CFGR>(0x00000000U);

    /* Reset HSEON, CSSON , HSION, and PLLON bits */
    rcc.get<CR>() &= 0xEAF6FFFFU;

    /* Reset PLLCFGR register */
    rcc.set<PLLCFGR>(0x00001000U);

    /* Reset HSEBYP bit */
    rcc.get<CR>() &= 0xFFFBFFFFU;

    /* Disable all interrupts */
    rcc.set<CIER>(0x00000000U);

    /* Configure the Vector Table location add offset address ------------------*/
  #ifdef VECT_TAB_SRAM
    scb.set<scb::VTOR>(kSramBase | kVectTabOffset); /* Vector Table Relocation in Internal SRAM */
  #else
    scb.set<scb::VTOR>(kFlashBase | kVectTabOffset); /* Vector Table Relocation in Internal FLASH */
  #endif
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
  constexpr std::array<uint8_t, 16u> AHBPrescTable {0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 1U, 2U, 3U, 4U, 6U, 7U, 8U, 9U};
  auto &rcc = *new ResetClockControl {};

  /*MSI frequency range in HZ*/
  auto msirange = GetMsiRangeFrequency();

  /* Get SYSCLK source -------------------------------------------------------*/
  SystemCoreClock = GetSysClkSource(msirange);

  /* Compute HCLK clock frequency --------------------------------------------*/
  /* Get HCLK prescaler */
  uint32_t tmp = AHBPrescTable[(rcc.And<ll::rcc::CFGR>(ll::rcc::cfgr::kHPre) >> 4U)];
  /* HCLK clock frequency */
  SystemCoreClock = hertz{static_cast<uint32_t>(SystemCoreClock.count()) >> tmp};
}
} // extern "C"
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
