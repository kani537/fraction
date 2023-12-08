#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <numeric>
#include <string>
#include <utility>

namespace mp = boost::multiprecision;

class frac {
 public:
  explicit frac(int numerator = 0) : top(numerator), bottom(1) { contract(); }
  explicit frac(int numerator, int denominator) : top(numerator), bottom(denominator) { contract(); }
  explicit frac(mp::cpp_int numerator) : top(numerator), bottom(1) { contract(); }
  explicit frac(mp::cpp_int numerator, mp::cpp_int denominator) : top(numerator), bottom(denominator) { contract(); }
  explicit frac(double _double) {
    double integral;
    double frac = std::modf(_double, &integral);

    int powerOfTen = 0;
    while (frac != std::floor(frac)) {
      frac *= 10;
      powerOfTen++;
    }

    top = mp::cpp_int(integral) * mp::pow(mp::cpp_int(10), powerOfTen) + mp::cpp_int(frac);
    bottom = mp::pow(mp::cpp_int(10), powerOfTen);
    contract();
  }
  explicit frac(std::pair<int, int> _pair) : top(_pair.first), bottom(_pair.second) { contract(); }
  explicit frac(const std::string &str) {
    top = 0;
    bottom = 1;
    for (auto c : str)
      if ('0' <= c && c <= '9') {
        top *= 10;
        top += c - '0';
      }
    auto pos = str.find('.');
    if (pos != std::string::npos)
      for (size_t i = 1; i < str.size() - pos; i++)
        bottom *= 10;
    contract();
  }

  mp::cpp_int get_top(void) const { return top; }
  mp::cpp_int get_bottom(void) const { return bottom; }
  double calc(void) const { return (double)top / (double)bottom; }
  std::string calc_str(size_t digit = 10) const {
    std::string str;
    auto _top = top;
    auto _bottom = bottom;

    if (_top < 0) {
      str += '-';
      _top = -_top;
    }

    if (_bottom <= _top) {
      str += (_top / _bottom).convert_to<std::string>();
      _top %= _bottom;
    } else
      str += '0';
    if (_top == 0)
      return str;
    str += '.';
    while (_top != 0 && str.size() < digit + 2) {
      _top *= 10;
      str += (_top / _bottom).convert_to<std::string>();
      _top %= _bottom;
    }
    return str;
  }
  frac abs(void) const { return frac(top < 0 ? -top : top, bottom); }
  frac inv(void) const { return frac(bottom, top); }
  frac pow(int n) const { return frac(mp::pow(top, n), mp::pow(bottom, n)); }

  frac operator+(const frac &_frac) const { return frac(top * _frac.bottom + _frac.top * bottom, bottom * _frac.bottom); }
  frac operator-() const { return frac(-top, bottom); }
  frac operator-(const frac &_frac) const { return *this + (-_frac); }
  frac operator*(const frac &_frac) const { return frac(top * _frac.top, bottom * _frac.bottom); }
  frac operator/(const frac &_frac) const { return frac(top * _frac.bottom, bottom * _frac.top); }

  void operator+=(const frac &_frac) { *this = *this + _frac; }
  void operator-=(const frac &_frac) { *this = *this - _frac; }
  void operator*=(const frac &_frac) { *this = *this * _frac; }
  void operator/=(const frac &_frac) { *this = *this / _frac; }
  bool operator==(const frac &_frac) const { return top == _frac.top && bottom == _frac.bottom; }
  bool operator!=(const frac &_frac) const { return !(*this == _frac); }
  bool operator<(const frac &_frac) const { return top * _frac.bottom < _frac.top * bottom; }
  bool operator<=(const frac &_frac) const { return top * _frac.bottom <= _frac.top * bottom; }
  bool operator>(const frac &_frac) const { return top * _frac.bottom > _frac.top * bottom; }
  bool operator>=(const frac &_frac) const { return top * _frac.bottom >= _frac.top * bottom; }

 private:
  mp::cpp_int top;
  mp::cpp_int bottom;

  void contract(void) {
    const mp::cpp_int gcd = mp::gcd(top, bottom);
    top /= gcd;
    bottom /= gcd;

    if (bottom < 0) {
      top = -top;
      bottom = -bottom;
    }
  }
};
