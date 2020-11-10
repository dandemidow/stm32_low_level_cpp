#if !defined(LL_GPIO_H_)
#define LL_GPIO_H_

#include "general_purpose_io.hpp"

namespace ll {

static inline void gpio_reset_output_pin(gpio::Pin &pin) {
  auto &port = pin.port();
  port.set<gpio::BRR>(pin.value());
}

static inline void gpio_set_pin_mode(gpio::Pin &pin, uint32_t mode) {
  const uint32_t position_pos = pin.position() * 2u;
  auto &port = pin.port();
  reg::modify(port.get<gpio::MODER>(),
              (gpio::kModerMode0 << position_pos),
              (mode << position_pos));
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

static inline void gpio_set_af_pin_8_15(GPIO_TypeDef *GPIOx, uint32_t Pin, uint32_t Alternate)
{
  MODIFY_REG(GPIOx->AFR[1], (GPIO_AFRH_AFSEL8 << (POSITION_VAL(Pin >> 8U) * 4U)),
             (Alternate << (POSITION_VAL(Pin >> 8U) * 4U)));
}

}  // namespace ll

#endif
