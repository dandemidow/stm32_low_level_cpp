#if !defined(LL_GPIO_H_)
#define LL_GPIO_H_

#include <cassert>

#include "general_purpose_io.hpp"

namespace ll {

enum class gpio_mode {
  Input = 0x00,
  Output = gpio::kModerMode00,
  Alternate = gpio::kModerMode01,
  Analog = gpio::kModerMode0
};

static inline void gpio_reset_output_pin(gpio::Pin &pin) {
  auto &port = pin.port();
  port.set<gpio::BRR>(pin.value());
}

static inline void gpio_set_pin_mode(gpio::Pin &pin, gpio_mode mode) {
  const uint32_t position_pin = pin.position() * 2u;
  auto &port = pin.port();
  reg::modify(port.get<gpio::MODER>(),
              (gpio::kModerMode0 << position_pin),
              (static_cast<uint32_t>(mode) << position_pin));
}

static inline void gpio_set_pin_speed(gpio::Pin &pin, uint32_t  speed) {
  const uint32_t position_pos = pin.position() * 2u;
  auto &port = pin.port();
  reg::modify(port.get<gpio::OSPEEDR>(),
              (gpio::kOspeedrOspeed0 << position_pos),
              (speed << position_pos));
}

static inline void gpio_set_pin_pull(gpio::Pin &pin, uint32_t pull) {
  const uint32_t position_pos = pin.position() * 2u;
  auto &port = pin.port();
  reg::modify(port.get<gpio::PUPDR>(),
              (gpio::kPupdrPupd0 << position_pos),
              (pull << position_pos));
}

static inline void gpio_set_af_pin_0_7(gpio::Pin &pin, uint32_t alternate) {
  const uint32_t position_pos = pin.position() * 4u;
  auto &port = pin.port();
  reg::modify(port.get<gpio::AFR>()[0],
              (gpio::kAfrlAfsel0 << position_pos),
              (alternate << position_pos));
}

static inline void gpio_set_af_pin_8_15(gpio::Pin &pin, uint32_t alternate) {
  assert(pin.position() >= 8u);
  const uint32_t position_pos = (pin.position() - 8u) * 4u;
  auto &port = pin.port();
  reg::modify(port.get<gpio::AFR>()[1],
              (gpio::kAfrlAfsel8 << position_pos),
              (alternate << position_pos));
}

static inline void gpio_set_pin_output_type(gpio::Pin &pin, uint32_t pin_mask, uint32_t output_type) {
  auto &port = pin.port();
  reg::modify(port.get<gpio::OTYPER>(),
              pin_mask,
              (pin_mask * output_type));
}

struct GPIOInitType {
  uint32_t Pin;
  gpio_mode Mode;
  uint32_t Speed;
  uint32_t OutputType;
  uint32_t Pull;
  uint32_t Alternate;
};

static bool gpio_init(gpio::Pin &pin, GPIOInitType *GPIO_InitStruct) {
  const uint32_t pinpos = pin.position();
  uint32_t currentpin;

  /* Check the parameters */
  assert_param(IS_LL_GPIO_PIN(GPIO_InitStruct->Pin));
  assert_param(IS_LL_GPIO_PULL(GPIO_InitStruct->Pull));

  auto &port = pin.port();

  /* Pin Mode configuration */
  gpio_set_pin_mode(pin, GPIO_InitStruct->Mode);

  if ((GPIO_InitStruct->Mode == gpio_mode::Output) ||
      (GPIO_InitStruct->Mode == gpio_mode::Analog)) {
        /* Check Speed mode parameters */
        assert_param(IS_LL_GPIO_SPEED(GPIO_InitStruct->Speed));

        /* Speed mode configuration */
        gpio_set_pin_speed(pin, GPIO_InitStruct->Speed);
      }

      /* Pull-up Pull down resistor configuration*/
      LL_GPIO_SetPinPull(GPIOx, currentpin, GPIO_InitStruct->Pull);

      if (GPIO_InitStruct->Mode == LL_GPIO_MODE_ALTERNATE)
      {
        /* Check Alternate parameter */
        assert_param(IS_LL_GPIO_ALTERNATE(GPIO_InitStruct->Alternate));

        /* Speed mode configuration */
        if (currentpin < LL_GPIO_PIN_8)
        {
          LL_GPIO_SetAFPin_0_7(GPIOx, currentpin, GPIO_InitStruct->Alternate);
        }
        else
        {
          LL_GPIO_SetAFPin_8_15(GPIOx, currentpin, GPIO_InitStruct->Alternate);
        }
      }

  if ((GPIO_InitStruct->Mode == LL_GPIO_MODE_OUTPUT) || (GPIO_InitStruct->Mode == LL_GPIO_MODE_ALTERNATE))
  {
    /* Check Output mode parameters */
    assert_param(IS_LL_GPIO_OUTPUT_TYPE(GPIO_InitStruct->OutputType));

    /* Output mode configuration*/
    LL_GPIO_SetPinOutputType(GPIOx, GPIO_InitStruct->Pin, GPIO_InitStruct->OutputType);

  }
  return (SUCCESS);
}


}  // namespace ll

#endif
