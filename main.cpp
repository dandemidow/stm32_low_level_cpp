/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2020 STMicroelectronics
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


#include "main.h"

#include "core_cm4.hpp"
#include "ll/gpio.h"
#include "ll/power.hpp"
#include "ll/rcc.hpp"
#include "ll/system.hpp"
#include "ll_bus.hpp"
#include "ll_cortex.hpp"
#include "ll_utils.hpp"

static void SystemClock_Config();
static void MX_GPIO_Init(ll::gpio::Pin &led);
static void LL_Init();

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main() {

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  LL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  ll::gpio::Pin led {ll::gpio::port::A, 5u};

  /* Initialize all configured peripherals */
  MX_GPIO_Init(led);

  /* Infinite loop */
  /* Toggle IO in an infinite loop */
  while (true) {
    led.toggle();

    /* Insert delay 1000 ms */
    ll::m_delay(1000);
  }
}

static void LL_Init(void) {
  ll::Apb2Grp1EnableClock(ll::kApb2Grp1PeriphSysCfg);
  ll::Apb2Grp1EnableClock(ll::kApb1Grp1PeriphPwr);

  nvic::set_priority_grouping(kNvicPriorityGroup4);

  /* System interrupt init*/
  /* MemoryManagement_IRQn interrupt configuration */
  nvic::set_priority(MemoryManagement_IRQn, nvic::encode_priority(nvic::get_priority_grouping(),0, 0));
  /* BusFault_IRQn interrupt configuration */
  nvic::set_priority(BusFault_IRQn, nvic::encode_priority(nvic::get_priority_grouping(),0, 0));
  /* UsageFault_IRQn interrupt configuration */
  nvic::set_priority(UsageFault_IRQn, nvic::encode_priority(nvic::get_priority_grouping(),0, 0));
  /* SVCall_IRQn interrupt configuration */
  nvic::set_priority(SVCall_IRQn, nvic::encode_priority(nvic::get_priority_grouping(),0, 0));
  /* DebugMonitor_IRQn interrupt configuration */
  nvic::set_priority(DebugMonitor_IRQn, nvic::encode_priority(nvic::get_priority_grouping(),0, 0));
  /* PendSV_IRQn interrupt configuration */
  nvic::set_priority(PendSV_IRQn, nvic::encode_priority(nvic::get_priority_grouping(),0, 0));
  /* SysTick_IRQn interrupt configuration */
  nvic::set_priority(SysTick_IRQn, nvic::encode_priority(nvic::get_priority_grouping(),0, 0));
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void) {

  ll::flash::set_latency(ll::flash::AcrLatency::kAcrLatency0);

  if(ll::flash::get_latency() != ll::flash::AcrLatency::kAcrLatency0) {
  Error_Handler();
  }
  ll::power::set_regul_voltage_scaling(ll::power::ReguVoltage::kScale1);

  ll::rcc_msi_enable();

   /* Wait till MSI is ready */
  while(ll::rcc_msi_is_ready() != true) {
  }

  ll::rcc_msi_enable_range_selection();

  ll::rcc_msi_set_range(GetRccCrMsiRange<6>());

  ll::rcc_msi_set_calib_trimming(0);

  ll::rcc_set_sys_clk_source(ll::RccSysClkSource::Msi);

   /* Wait till System clock is ready */
  while(ll::rcc_get_sys_clk_source() != ll::RccSysClkSourceStatus::Msi) {
  }

  ll::rcc_set_ahb_prescaler(ll::RccSysClkDiv::Div1);

  ll::rcc_set_apb1_prescaler(ll::RccApb1Div::Div1);

  ll::rcc_set_apb2_prescaler(ll::RccApb2Div::Div1);

  ll::init_1ms_tick(4000000);

  ll::sys_tick_set_clk_source(sys_tick::kClkSourceHCLK);

  ll::set_system_core_clock(4000000);

  /* SysTick_IRQn interrupt configuration */
  nvic::set_priority(SysTick_IRQn, nvic::encode_priority(nvic::get_priority_grouping(),0, 0));
}

static void MX_GPIO_Init(ll::gpio::Pin &led) {
  /* GPIO Ports Clock Enable */
  ll::Ahb2Grp1EnableClock(ll::kAhb2Grp1PeriphGpioA);

  /*led.reset_output*/
  led.reset_output();

  /**/
  ll::gpio::init_cfg gpio_init {
    .Mode = ll::gpio::mode::Output,
    .Speed = ll::gpio::speed::VeryHigh,
    .OutputType = ll::gpio::output::PushPull,
    .Pull = ll::gpio::pull::Up,
    .Alternate = ll::gpio::alternate::kAf0
  };
  led.init(gpio_init);
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler([[maybe_unused]] const char *file, [[maybe_unused]] int line) {
  while(1) {
  }
}

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
