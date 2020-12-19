#if !defined(LL_FRECUENCY_H_)
#define LL_FRECUENCY_H_

#include <ratio>

template <class> class Frequency;
using hertz = Frequency<std::ratio<1>>;
using kilohertz = Frequency<std::kilo>;
using megahertz = Frequency<std::mega>;

template <class Ratio>
class Frequency {
 private:
  uint32_t value {0u};
 public:
  using ratio = Ratio;

  constexpr Frequency() = default;
  constexpr explicit Frequency(uint32_t v) : value{v} {}

  template <class R>
  constexpr Frequency(const Frequency<R>& d)
      : value(d.count() * std::ratio_divide<Ratio, R>::type::den /
                          std::ratio_divide<Ratio, R>::type::num) {}

  constexpr uint32_t count() const {return value;}

  constexpr Frequency operator+(const Frequency& d) const {return Frequency{value + d.count()};}
  constexpr Frequency operator-(const Frequency& d) const {return Frequency{value - d.count()};}

  constexpr Frequency operator*(uint32_t rhs) const {return Frequency{value * rhs};}
  hertz operator/(uint32_t rhs) const {hertz tmp = *this; return hertz{tmp.count() / rhs};}

  constexpr Frequency& operator+=(const Frequency& d) {value += d.count(); return *this;}
  constexpr Frequency& operator-=(const Frequency& d) {value -= d.count(); return *this;}

  constexpr Frequency operator+() const {return *this;}
  constexpr Frequency operator-() const {return Frequency(-value);}
};

constexpr hertz operator""_Hz ( unsigned long long int freq ) {
  return hertz{static_cast<uint32_t>(freq)};
}

constexpr kilohertz operator""_KHz ( unsigned long long int freq ) {
  return kilohertz{static_cast<uint32_t>(freq)};
}

constexpr megahertz operator""_MHz ( unsigned long long int freq ) {
  return megahertz{static_cast<uint32_t>(freq)};
}

#endif
