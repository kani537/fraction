#include "fraction.hpp"

frac::frac(double _double) {
  top = 0;
  bottom = 1;
  while (_double != (int)_double && bottom < 1e9) {
    _double *= 10;
    bottom *= 10;
  }
  top = _double;
  contract();
}

frac::frac(const std::string &str) {
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

int frac::get_top(void) { return top; }

int frac::get_bottom(void) { return bottom; }

double frac::calc(void) const { return (double)top / bottom; }

std::string frac::calc_str(size_t digit) const {
  std::string ret = "";

  auto tmp = top;
  bool flag = true;

  if(tmp < 0) {
    ret += "-";
    tmp = -tmp;
  }

  while (ret.size() < digit + 1) {
    ret += std::to_string(tmp / bottom);
    tmp %= bottom;
    tmp *= 10;
    if (!tmp)
      break;
    if (flag) {
      ret += ".";
      flag = false;
    }
  }

  return ret;
}

frac frac::operator+(const frac &_frac) const {
  return frac(top * _frac.bottom + _frac.top * bottom, bottom * _frac.bottom);
}

frac frac::operator-() const {
  return frac(-top, bottom);
}

frac frac::operator-(const frac &_frac) const {
  return frac(top * _frac.bottom - _frac.top * bottom, bottom * _frac.bottom);
}

frac frac::operator*(const frac &_frac) const {
  return frac(top * _frac.top, bottom * _frac.bottom);
}

frac frac::operator/(const frac &_frac) const {
  return frac(top * _frac.bottom, bottom * _frac.top);
}

void frac::operator+=(const frac &_frac) {
  top *= _frac.bottom;
  top += _frac.top * bottom;
  bottom *= _frac.bottom;
  contract();
}

void frac::operator-=(const frac &_frac) {
  top *= _frac.bottom;
  top -= _frac.top * bottom;
  bottom *= _frac.bottom;
  contract();
}

void frac::operator*=(const frac &_frac) {
  top *= _frac.top;
  bottom *= _frac.bottom;
  contract();
}

void frac::operator/=(const frac &_frac) {
  top *= _frac.bottom;
  bottom *= _frac.top;
  contract();
}

bool frac::operator==(const frac &_frac) const {
  return top == _frac.top && bottom == _frac.bottom;
}

bool frac::operator!=(const frac &_frac) const {
  return !(*this == _frac);
}

bool frac::operator<(const frac &_frac) const {
  return top * _frac.bottom < _frac.top * bottom;
}

bool frac::operator<=(const frac &_frac) const {
  return top * _frac.bottom <= _frac.top * bottom;
}

bool frac::operator>(const frac &_frac) const {
  return top * _frac.bottom > _frac.top * bottom;
}

bool frac::operator>=(const frac &_frac) const {
  return top * _frac.bottom >= _frac.top * bottom;
}

void frac::contract(void) {
  auto gcd = std::gcd(top, bottom);
  top /= gcd;
  bottom /= gcd;

  if (bottom < 0) {
    top = -top;
    bottom = -bottom;
  }
}
