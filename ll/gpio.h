#if !defined(LL_GPIO_H_)
#define LL_GPIO_H_

#include "general_purpose_io.hpp"

namespace ll {

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

namespace gpio {

enum class mode {
  Input = 0x00,
  Output = gpio::kModerMode00,
  Alternate = gpio::kModerMode01,
  Analog = gpio::kModerMode0
};

enum class speed {
  Low = 0x00,
  Medium = gpio::kOspeedrOspeed00,
  High = gpio::kOspeedrOspeed01,
  VeryHigh = gpio::kOspeedrOspeed0
};

class Pin {
 public:
  Pin(port p, uint32_t number)
    : gpio_ {*new (p) GeneralPurposeIO{}},
      number_ {number},
      value_ {0x01u << number} {}

  inline uint32_t position() const { return number_; }
  inline uint32_t value() const { return value_; }
  inline GeneralPurposeIO &get_port() { return gpio_; }

  inline void reset_output() {
    gpio_.set<BRR>(value_);
  }
  void set_mode(mode mode);
  void set_speed(speed speed);

 private:
  GeneralPurposeIO &gpio_;
  const uint32_t number_;
  const uint32_t value_;
};

}  // namespace gpio

struct GPIOInitType {
  gpio::mode   Mode;
  gpio::speed  Speed;
  gpio_output OutputType;
  gpio_pull   Pull;
  gpio_alternate Alternate;
};

static inline void gpio_set_pin_pull(ll::gpio::Pin &pin, gpio_pull pull) {
  const uint32_t position_pos = pin.position() * 2u;
  auto &port = pin.get_port();
  reg::modify(port.get<gpio::PUPDR>(),
              (gpio::kPupdrPupd0 << position_pos),
              (static_cast<uint32_t>(pull) << position_pos));
}

static inline void gpio_set_af_pin_0_7(ll::gpio::Pin &pin, gpio_alternate alternate) {
  const uint32_t position_pos = pin.position() * 4u;
  auto &port = pin.get_port();
  reg::modify(port.get<gpio::AFR>()[0],
              (gpio::kAfrlAfsel0 << position_pos),
              (static_cast<uint32_t>(alternate) << position_pos));
}

static inline void gpio_set_af_pin_8_15(ll::gpio::Pin &pin, gpio_alternate alternate) {
//  assert(pin.position() >= 8u);
  const uint32_t position_pos = (pin.position() - 8u) * 4u;
  auto &port = pin.get_port();
  reg::modify(port.get<gpio::AFR>()[1],
              (gpio::kAfrlAfsel8 << position_pos),
              (static_cast<uint32_t>(alternate) << position_pos));
}

static inline void gpio_set_pin_output_type(ll::gpio::Pin &pin, uint32_t pin_mask, gpio_output output_type) {
  auto &port = pin.get_port();
  reg::modify(port.get<gpio::OTYPER>(),
              pin_mask,
              (pin_mask * static_cast<uint32_t>(output_type)));
}

static inline void gpio_toggle_pin(ll::gpio::Pin &pin) {
  auto &port = pin.get_port();
  uint32_t pin_mask = pin.value();
  uint32_t odr = port.get<gpio::ODR>();
  port.set<gpio::BSRR>(((odr & pin_mask) << 16u) | (~odr & pin_mask));
}

bool gpio_init(ll::gpio::Pin &pin, const GPIOInitType &init);

}  // namespace ll

#endif
