#if !defined(DEVICE_REGISTER_H_)
#define DEVICE_REGISTER_H_

#include <cstdint>
#include <cstddef>
#include <type_traits>

using RegByte = volatile uint8_t;
using Register = volatile uint32_t;
using ReadOnlyRegister = volatile uint32_t const;

template <uint32_t Mask, size_t Position>
struct Flag {
static constexpr uint32_t value = (Mask << Position);
};

namespace bit {
enum {
  RESET = 0,
  SET = !RESET
};

}  // namespace bit

#endif
