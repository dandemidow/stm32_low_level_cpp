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

#include "ll/bus.hpp"
#include "ll/core.h"
#include "ll/cortex.hpp"
#include "ll/gpio.h"
#include "ll/msi.h"
#include "ll/power.hpp"
#include "ll/system.hpp"
#include "ll/spinlock.hpp"
#include "ll/utils.hpp"

static void SystemClock_Config();
static void MX_GPIO_Init(ll::gpio::Pin &led);
static void LL_Init();
static void _Error_Handler(const char *, int);

using namespace std::chrono_literals;

int main() {

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  LL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  ll::gpio::Pin led {ll::gpio::port::A, 5u};

  /* Initialize all configured peripherals */
  MX_GPIO_Init(led);

  while (true) {
    led.toggle();
    ll::delay(1000ms);
  }
}

static void LL_Init(void) {
  ll::bus::Grp1EnableClock(ll::bus::apb2::kGrp1PeriphSysCfg);
  ll::bus::Grp1EnableClock(ll::bus::apb1::kGrp1PeriphPwr);

  ll::nvic::set_priority_grouping(ll::nvic::PriorityGroup::Gr4);

  /* System interrupt init*/
  /* MemoryManagement_IRQn interrupt configuration */
  ll::nvic::set_priority(MemoryManagement_IRQn);
  /* BusFault_IRQn interrupt configuration */
  ll::nvic::set_priority(BusFault_IRQn);
  /* UsageFault_IRQn interrupt configuration */
  ll::nvic::set_priority(UsageFault_IRQn);
  /* SVCall_IRQn interrupt configuration */
  ll::nvic::set_priority(SVCall_IRQn);
  /* DebugMonitor_IRQn interrupt configuration */
  ll::nvic::set_priority(DebugMonitor_IRQn);
  /* PendSV_IRQn interrupt configuration */
  ll::nvic::set_priority(PendSV_IRQn);
  /* SysTick_IRQn interrupt configuration */
  ll::nvic::set_priority(SysTick_IRQn);
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config() {

  ll::flash::set_latency(ll::flash::AcrLatency::kAcrLatency0);

  if(ll::flash::get_latency() != ll::flash::AcrLatency::kAcrLatency0) {
    _Error_Handler(__FILE__, __LINE__);
  }
  ll::power::set_regul_voltage_scaling(ll::power::ReguVoltage::kScale1);

  ll::Msi msi{};
  msi.Enable();
  SpinLock::Till([&]{return msi.IsReady();});

  msi.EnableRangeSelection();
  msi.SetRange(ll::rcc::GetRccCrMsiRange<6>());
  msi.SetCalibTrimming(0);

  ll::rcc::set_sys_clk_source(msi);

   /* Wait till System clock is ready */
  SpinLock::Till([&]{return ll::rcc::get_sys_clk_source() == msi;});

  ll::rcc::set_ahb_prescaler(ll::rcc::SysClkDiv::Div1);

  ll::rcc::set_apb1_prescaler(ll::rcc::Apb1Div::Div1);

  ll::rcc::set_apb2_prescaler(ll::rcc::Apb2Div::Div1);

  constexpr auto kBaseFrequency = 4_KHz;

  ll::tick::init_1ms(kBaseFrequency);

  ll::tick::sys_set_clk_source(ll::tick::kClkSourceHCLK);

  ll::set_system_core_clock(kBaseFrequency);

  /* SysTick_IRQn interrupt configuration */
  ll::nvic::set_priority(IRQn_Type::SysTick_IRQn);
}

static void MX_GPIO_Init(ll::gpio::Pin &led) {
  /* GPIO Ports Clock Enable */
  ll::bus::Grp1EnableClock(ll::bus::ahb2::kGrp1PeriphGpioA);

  led.reset_output();

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
