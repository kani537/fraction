#include "fraction.hpp"

frac::frac(int numerator) {
  top = numerator;
  bottom = 1;
  contract();
}

frac::frac(int numerator, int denominator) {
  top = numerator;
  bottom = denominator;
  contract();
}

frac::frac(std::pair<int, int> _pair) {
  top = _pair.first;
  bottom = _pair.second;
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
  while (ret.size() < digit + 1) {
    ret += std::to_string(tmp / bottom);
    tmp %= bottom;
    tmp *= 10;
    if (flag) {
      ret += ".";
      flag = false;
    }
    if (!tmp)
      break;
  }

  return ret;
}

frac frac::operator+(frac _frac) const {
  frac ret(*this);
  ret += _frac;
  return ret;
}

frac frac::operator-() const {
  frac ret(*this);
  ret.top *= -1;
  return ret;
}

frac frac::operator-(frac _frac) const {
  frac ret(*this);
  ret -= _frac;
  return ret;
}

frac frac::operator*(frac _frac) const {
  frac ret(*this);
  ret *= _frac;
  return ret;
}

frac frac::operator/(frac _frac) const {
  frac ret(*this);
  ret /= _frac;
  return ret;
}

void frac::operator+=(frac _frac) {
  auto lcm = std::lcm(bottom, _frac.bottom);
  top *= lcm / bottom;
  top += _frac.top * (lcm / _frac.bottom);
  bottom = lcm;
  contract();
}

void frac::operator-=(frac _frac) {
  auto lcm = std::lcm(bottom, _frac.bottom);
  top *= lcm / bottom;
  top -= _frac.top * (lcm / _frac.bottom);
  bottom = lcm;
  contract();
}

void frac::operator*=(frac _frac) {
  top *= _frac.top;
  bottom *= _frac.bottom;
  contract();
}

void frac::operator/=(frac _frac) {
  top *= _frac.bottom;
  bottom *= _frac.top;
  contract();
}

bool frac::operator==(frac _frac) const {
  return top == _frac.top && bottom == _frac.bottom;
}

bool frac::operator!=(frac _frac) const {
  return !(*this == _frac);
}

bool frac::operator<(frac _frac) const {
  return top * _frac.bottom < _frac.top * bottom;
}

bool frac::operator<=(frac _frac) const {
  return top * _frac.bottom <= _frac.top * bottom;
}

bool frac::operator>(frac _frac) const {
  return top * _frac.bottom > _frac.top * bottom;
}

bool frac::operator>=(frac _frac) const {
  return top * _frac.bottom >= _frac.top * bottom;
}

void frac::contract(void) {
  auto gcd = std::gcd(top, bottom);
  top /= gcd;
  bottom /= gcd;
  frac a = 1;
}
