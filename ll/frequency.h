#if !defined(LL_FRECUENCY_H_)
#define LL_UTILS_H_

#include <ratio>

template <class Ratio>
class Frequency {
 private:
  double value {0.0};
 public:
  typedef Ratio ratio;

  constexpr Frequency() = default;
  Frequency(const double& v) : value(v) {}

  template <class R>
  Frequency(const Frequency<R>& d)
      : value(d.count() * std::ratio_divide<Ratio, R>::type::den /
                          std::ratio_divide<Ratio, R>::type::num) {}

  double count() const {return value;}

  Frequency operator+(const Frequency& d) {return {value + d.count()};}
  Frequency operator-(const Frequency& d) {return {value - d.count()};}

  Frequency& operator+=(const Frequency& d) {value += d.count(); return *this;}
  Frequency& operator-=(const Frequency& d) {value -= d.count(); return *this;}

  Frequency operator+() const {return *this;}
  Frequency operator-() const {return Frequency(-value);}

  Frequency& operator*=(double rhs) {value *= rhs; return *this;}
  Frequency& operator/=(double rhs) {value /= rhs; return *this;}
};

using hertz = Frequency<std::ratio<1>>;
using kilohertz = Frequency<std::kilo>;
using megahertz = Frequency<std::mega>;

constexpr kilohertz operator""_KHz ( long double freq ) {
  return kilohertz{static_cast<double>(freq)};
}

constexpr kilohertz operator""_KHz ( unsigned long long int freq ) {
  return kilohertz{static_cast<double>(freq)};
}

#endif
