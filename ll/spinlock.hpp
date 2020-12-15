#if !defined(LL_SPINLOCK_H_)
#define LL_SPINLOCK_H_

#include <concepts>

struct SpinLock {
  static constexpr void Till(std::predicate auto cond) {
    while (!cond()) {}
  }
};

#endif
