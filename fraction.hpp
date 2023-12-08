#include <numeric>
#include <string>
#include <utility>

class frac {
 public:
  explicit frac(int numerator = 0) : top(numerator), bottom(1) { contract(); }
  explicit frac(int numerator, int denominator) : top(numerator), bottom(denominator) { contract(); }
  explicit frac(double _double) {
    top = 0;
    bottom = 1;
    while (_double != (int)_double && bottom < 1e9) {
      _double *= 10;
      bottom *= 10;
    }
    top = _double;
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

  int get_top(void) const { return top; }
  int get_bottom(void) const { return bottom; }
  double calc(void) const { return (double)top / bottom; }
  std::string calc_str(size_t digit = 10) const {
    std::string str;
    auto _top = top;
    auto _bottom = bottom;

    if(_top < 0) {
      str += '-';
      _top = -_top;
    }

    while (_bottom <= _top) {
      str += std::to_string(_top / _bottom);
      _top %= _bottom;
    }
    if (_top == 0)
      return str.empty() ? "0" : str;
    str += '.';
    while (_top != 0 && str.size() < digit + 2) {
      _top *= 10;
      str += std::to_string(_top / _bottom);
      _top %= _bottom;
    }
    return str;
  }

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
  int64_t top;
  int64_t bottom;
  void contract(void) {
    auto gcd = std::gcd(top, bottom);
    top /= gcd;
    bottom /= gcd;

    if (bottom < 0) {
      top = -top;
      bottom = -bottom;
    }
  }
};
