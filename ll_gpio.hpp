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

enum class gpio_alternate {
  kAf0 = 0x00,
  kAf1,
  kAf2,
  kAf3,
  kAf4,
  kAf5,
  kAf6,
  kAf7,
  kAf8,
  kAf9,
  kAf10,
  kAf11,
  kAf12,
  kAf13,
  kAf14,
  kAf15,
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

static inline void gpio_set_af_pin_0_7(gpio::Pin &pin, gpio_alternate alternate) {
  const uint32_t position_pos = pin.position() * 4u;
  auto &port = pin.port();
  reg::modify(port.get<gpio::AFR>()[0],
              (gpio::kAfrlAfsel0 << position_pos),
              (static_cast<uint32_t>(alternate) << position_pos));
}

static inline void gpio_set_af_pin_8_15(gpio::Pin &pin, gpio_alternate alternate) {
  assert(pin.position() >= 8u);
  const uint32_t position_pos = (pin.position() - 8u) * 4u;
  auto &port = pin.port();
  reg::modify(port.get<gpio::AFR>()[1],
              (gpio::kAfrlAfsel8 << position_pos),
              (static_cast<uint32_t>(alternate) << position_pos));
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
  gpio_alternate Alternate;
};

static bool gpio_init(gpio::Pin &pin, GPIOInitType &init) {
  /* Pin Mode configuration */
  gpio_set_pin_mode(pin, init.Mode);

  if ((init.Mode == gpio_mode::Output) ||
      (init.Mode == gpio_mode::Analog)) {
        /* Speed mode configuration */
        gpio_set_pin_speed(pin, init.Speed);
  }

  /* Pull-up Pull down resistor configuration*/
  gpio_set_pin_pull(pin, init.Pull);

  if (init.Mode == gpio_mode::Alternate) {
    /* Speed mode configuration */
    if (pin.value() < gpio::kPin8) {
      gpio_set_af_pin_0_7(pin, init.Alternate);
    } else {
      gpio_set_af_pin_8_15(pin, init.Alternate);
    }
  }

  if ((init.Mode == gpio_mode::Output) ||
      (init.Mode == gpio_mode::Alternate)) {
    /* Output mode configuration*/
    gpio_set_pin_output_type(pin, init.Pin, init.OutputType);
  }
  return true;
}


}  // namespace ll

#endif
