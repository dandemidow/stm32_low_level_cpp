#if !defined(LL_GPIO_PIN_H_)
#define LL_GPIO_PIN_H_

#include "bus.hpp"
#include "register/general_purpose_io.hpp"
#include "register/gpio_bus.h"

namespace ll::gpio {
using namespace address::gpio;
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

enum class pull {
  No = 0x00,
  Up = gpio::kPupdrPupd00,
  Down = gpio::kPupdrPupd01
};

enum class alternate {
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

enum class output {
  PushPull = 0x00,
  OpenDrain = gpio::kOTypeR0
};

struct init_cfg {
  gpio::mode   Mode;
  gpio::speed  Speed;
  gpio::output OutputType;
  gpio::pull   Pull;
  gpio::alternate Alternate;
};

class Pin {
 public:
  Pin(port p, uint32_t number)
    : gpio_ {*new (p) GeneralPurposeIO{}},
      number_ {number},
      value_ {0b1 << number} {
    EnablePort(p);
  }

  inline uint32_t position() const { return number_; }
  inline uint32_t value() const { return value_; }
  inline GeneralPurposeIO &get_port() { return gpio_; }

  void set_mode(mode mode);
  inline void set_speed(speed speed) {
    const uint32_t position_pin = number_ * 2u;
    reg::modify(gpio_.get<OSPEEDR>(),
                (gpio::kOspeedrOspeed0 << position_pin),
                (static_cast<uint32_t>(speed) << position_pin));
  }
  inline void set_pull(pull pull) {
    const uint32_t position_pin = number_ * 2u;
    reg::modify(gpio_.get<gpio::PUPDR>(),
                (gpio::kPupdrPupd0 << position_pin),
                (static_cast<uint32_t>(pull) << position_pin));
  }
  inline void set_af(alternate alternate) {
    uint32_t position_pin = number_ * 4u;
    if (value_ < kPin8) {
      reg::modify(gpio_.get<gpio::AFR>()[0],
                  (kAfrlAfsel0 << position_pin),
                  (static_cast<uint32_t>(alternate) << position_pin));
    } else {
      position_pin = position_pin - 8u * 4u;
      reg::modify(gpio_.get<gpio::AFR>()[1],
                  (kAfrlAfsel8 << position_pin),
                  (static_cast<uint32_t>(alternate) << position_pin));
    }
  }

  inline void set_output_type(uint32_t pin_mask, output output_type) {
    reg::modify(gpio_.get<gpio::OTYPER>(),
                pin_mask,
                (pin_mask * static_cast<uint32_t>(output_type)));
  }

  inline void toggle() {
    uint32_t odr = gpio_.get<ODR>();
    gpio_.set<BSRR>(((odr & value_) << 16u) | (~odr & value_));
  }

  [[deprecated]]
  bool init(const init_cfg &init);

 protected:
  GeneralPurposeIO &gpio_;
  const uint32_t number_;
  const uint32_t value_;
};

}  // namespace ll::gpio

#endif
