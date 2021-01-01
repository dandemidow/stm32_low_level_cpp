#if !defined(REGISTER_VALUE_HPP_)
#define REGISTER_VALUE_HPP_

#include <cstdint>
#include <cstddef>

#include "device_register.h"

template <uint32_t RegisterId>
struct RegisterValue {
  static constexpr auto kReg = RegisterId;
  uint32_t value;
  template <uint32_t Mask, size_t Position>
  constexpr RegisterValue(const Flag<Mask, Position> &flag)
    : value {flag} {}
};

#endif
