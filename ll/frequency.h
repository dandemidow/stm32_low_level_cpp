#if !defined(LL_FRECUENCY_H_)
#define LL_FRECUENCY_H_

#include <ratio>

template <class Ratio>
class Frequency {
 private:
  double value {0.0};
 public:
  using ratio = Ratio;

  constexpr Frequency() = default;
  constexpr Frequency(const double& v) : value(v) {}

  template <class R>
  constexpr Frequency(const Frequency<R>& d)
      : value(d.count() * std::ratio_divide<Ratio, R>::type::den /
                          std::ratio_divide<Ratio, R>::type::num) {}

  constexpr double count() const {return value;}

  constexpr Frequency operator+(const Frequency& d) {return {value + d.count()};}
  constexpr Frequency operator-(const Frequency& d) {return {value - d.count()};}

  constexpr Frequency& operator+=(const Frequency& d) {value += d.count(); return *this;}
  constexpr Frequency& operator-=(const Frequency& d) {value -= d.count(); return *this;}

  constexpr Frequency operator+() const {return *this;}
  constexpr Frequency operator-() const {return Frequency(-value);}

  constexpr Frequency& operator*=(double rhs) {value *= rhs; return *this;}
  constexpr Frequency& operator/=(double rhs) {value /= rhs; return *this;}
};

using hertz = Frequency<std::ratio<1>>;
using kilohertz = Frequency<std::kilo>;
using megahertz = Frequency<std::mega>;

constexpr auto operator""_Hz ( long double freq ) {
  return hertz{static_cast<double>(freq)};
}

constexpr hertz operator""_Hz ( unsigned long long int freq ) {
  return hertz{static_cast<double>(freq)};
}

constexpr kilohertz operator""_KHz ( long double freq ) {
  return kilohertz{static_cast<double>(freq)};
}

constexpr kilohertz operator""_KHz ( unsigned long long int freq ) {
  return kilohertz{static_cast<double>(freq)};
}

constexpr megahertz operator""_MHz ( long double freq ) {
  return megahertz{static_cast<double>(freq)};
}

constexpr megahertz operator""_MHz ( unsigned long long int freq ) {
  return megahertz{static_cast<double>(freq)};
}

#endif
