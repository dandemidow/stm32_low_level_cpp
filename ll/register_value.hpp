#if !defined(REGISTER_VALUE_HPP_)
#define REGISTER_VALUE_HPP_

#include <cstdint>
#include <cstddef>

#include "device_register.h"

template <uint32_t RegisterId>
struct RegisterValue {
  static constexpr auto kReg = RegisterId;
  uint32_t value;
  constexpr operator uint32_t() const {
    return value;
  }
};

#endif
