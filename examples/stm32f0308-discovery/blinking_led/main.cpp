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

#include "bus.hpp"
#include "core.h"
#include "cortex.hpp"
#include "gpio/output.h"
#include "hsi.h"
#include "pll.h"
#include "system.hpp"
#include "spinlock.hpp"
#include "utils.hpp"

static void SystemClock_Config();
static void LL_Init();
static void _Error_Handler(const char *, int);

using namespace std::chrono_literals;

void  Configure_TIMTimeBase(void)
{
  /* Enable the timer peripheral clock */
  ll::bus::GrpEnableClock(ll::rcc::kApb2Grp1PeriphTim1);

  /* Set counter mode */
  /* Reset value is LL_TIM_COUNTERMODE_UP */
  //LL_TIM_SetCounterMode(TIM1, LL_TIM_COUNTERMODE_UP);

  /* Set the pre-scaler value to have TIM1 counter clock equal to 10 kHz      */
  /*
   In this example TIM1 input clock TIM1CLK is set to APB2 clock (PCLK2),
   since APB2 pre-scaler is equal to 1.
      TIM1CLK = PCLK2
      PCLK2 = HCLK
      => TIM1CLK = SystemCoreClock (80 MHz)
  */
  LL_TIM_SetPrescaler(TIM1, __LL_TIM_CALC_PSC(SystemCoreClock, 10000));

  /* Set the auto-reload value to have an initial update event frequency of 10 Hz */
  InitialAutoreload = __LL_TIM_CALC_ARR(SystemCoreClock, LL_TIM_GetPrescaler(TIM1), 10);
  LL_TIM_SetAutoReload(TIM1, InitialAutoreload);

  /* Enable the update interrupt */
  LL_TIM_EnableIT_UPDATE(TIM1);

  /* Configure the NVIC to handle TIM1 update interrupt */
  NVIC_SetPriority(TIM1_UP_TIM16_IRQn, 0);
  NVIC_EnableIRQ(TIM1_UP_TIM16_IRQn);

  /* Enable counter */
  LL_TIM_EnableCounter(TIM1);

  /* Force update generation */
  LL_TIM_GenerateEvent_UPDATE(TIM1);
}


int main() {

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  LL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  ll::gpio::Output led3 {ll::gpio::port::C, 9u};
  ll::gpio::Output led4 {ll::gpio::port::C, 8u};

  led3.init(ll::gpio::output::PushPull,
            ll::gpio::pull::Up,
            ll::gpio::speed::VeryHigh);

  led4.init(ll::gpio::output::PushPull,
            ll::gpio::pull::Up,
            ll::gpio::speed::VeryHigh);

  while (true) {
    led3.toggle();
    ll::delay(500ms);
    led4.toggle();
    ll::delay(500ms);
  }
}

static void LL_Init(void) {
  ll::bus::GrpEnableClock(ll::rcc::kApb1Grp2PeriphSysCfg);

  /* System interrupt init*/
  /* MemoryManagement_IRQn interrupt configuration */
  ll::nvic::set_priority(IRQn_Type::SVC_IRQn);
  /* BusFault_IRQn interrupt configuration */
  ll::nvic::set_priority(IRQn_Type::PendSV_IRQn);
  /* SysTick_IRQn interrupt configuration */
  ll::nvic::set_priority(IRQn_Type::SysTick_IRQn);
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config() {

  ll::flash::set_latency(ll::flash::AcrLatency::kAcrLatency1);

  if(ll::flash::get_latency() != ll::flash::AcrLatency::kAcrLatency1) {
    _Error_Handler(__FILE__, __LINE__);
  }

  ll::Hsi hsi{};
  hsi.Enable();
  SpinLock::Till([&]{return hsi.IsReady();});

  hsi.SetCalibTrimming(ll::rcc::cr::HsiTrim::HsiTrim4);

  ll::Pll pll {ll::rcc::cfgr::PllSrc::HsiDiv2, ll::rcc::cfgr::PllMul::PllMul12};
  pll.Enable();
  SpinLock::Till([&]{return pll.IsReady();});

  ll::rcc::SystemClock sys_clock;
  sys_clock << ll::rcc::cfgr::kHPreDiv<ll::rcc::cfgr::HPreDiv::Div1>
            << ll::rcc::cfgr::kPPreDiv<ll::rcc::cfgr::PPreDiv::Div1>
            << pll;

   /* Wait till System clock is ready */
  SpinLock::Till([&]{return sys_clock.get_source() == pll;});

  constexpr auto kBaseFrequency = 48_MHz;

  ll::tick::init_1ms(kBaseFrequency);

  ll::tick::sys_set_clk_source(ll::tick::kClkSourceHCLK);

  ll::set_system_core_clock(kBaseFrequency);

  /* SysTick_IRQn interrupt configuration */
  ll::nvic::set_priority(IRQn_Type::SysTick_IRQn);
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
