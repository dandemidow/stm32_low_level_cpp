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

enum class gpio_speed {
  Low = 0x00,
  Medium = gpio::kOspeedrOspeed00,
  High = gpio::kOspeedrOspeed01,
  VeryHigh = gpio::kOspeedrOspeed0
};

enum class gpio_pull {
  No = 0x00,
  Up = gpio::kPupdrPupd00,
  Down = gpio::kPupdrPupd01
};

enum class gpio_output {
  PushPull = 0x00,
  OpenDrain = gpio::kOTypeR0
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

static inline void gpio_set_pin_speed(gpio::Pin &pin, gpio_speed  speed) {
  const uint32_t position_pos = pin.position() * 2u;
  auto &port = pin.port();
  reg::modify(port.get<gpio::OSPEEDR>(),
              (gpio::kOspeedrOspeed0 << position_pos),
              (static_cast<uint32_t>(speed) << position_pos));
}

static inline void gpio_set_pin_pull(gpio::Pin &pin, gpio_pull pull) {
  const uint32_t position_pos = pin.position() * 2u;
  auto &port = pin.port();
  reg::modify(port.get<gpio::PUPDR>(),
              (gpio::kPupdrPupd0 << position_pos),
              (static_cast<uint32_t>(pull) << position_pos));
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

static inline void gpio_set_pin_output_type(gpio::Pin &pin, uint32_t pin_mask, gpio_output output_type) {
  auto &port = pin.port();
  reg::modify(port.get<gpio::OTYPER>(),
              pin_mask,
              (pin_mask * static_cast<uint32_t>(output_type)));
}

struct GPIOInitType {
  uint32_t Pin;
  gpio_mode   Mode;
  gpio_speed  Speed;
  gpio_output OutputType;
  gpio_pull   Pull;
  uint32_t Alternate;
};

static bool gpio_init(gpio::Pin &pin, GPIOInitType *GPIO_InitStruct) {
  /* Pin Mode configuration */
  gpio_set_pin_mode(pin, GPIO_InitStruct->Mode);

  if ((GPIO_InitStruct->Mode == gpio_mode::Output) ||
      (GPIO_InitStruct->Mode == gpio_mode::Analog)) {
        /* Speed mode configuration */
        gpio_set_pin_speed(pin, GPIO_InitStruct->Speed);
      }

      /* Pull-up Pull down resistor configuration*/
      gpio_set_pin_pull(pin, GPIO_InitStruct->Pull);

      if (GPIO_InitStruct->Mode == gpio_mode::Alternate) {
        /* Speed mode configuration */
        if (pin.value() < gpio::kPin8) {
          gpio_set_af_pin_0_7(pin, GPIO_InitStruct->Alternate);
        } else {
          gpio_set_af_pin_8_15(pin, GPIO_InitStruct->Alternate);
        }
      }

  if ((GPIO_InitStruct->Mode == gpio_mode::Output) ||
      (GPIO_InitStruct->Mode == gpio_mode::Alternate)) {
    /* Output mode configuration*/
    gpio_set_pin_output_type(pin, GPIO_InitStruct->Pin, GPIO_InitStruct->OutputType);

  }
  return true;
}


}  // namespace ll

#endif
