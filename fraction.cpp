#include "fraction.hpp"

frac::frac(int modelcure, int denominator) {
  mode = modelcure;
  deno = denominator;
  contract();
}

frac::frac(std::pair<int, int> _pair) {
  mode = _pair.first;
  deno = _pair.second;
  contract();
}

frac::frac(const std::string &str) {
  mode = 0;
  deno = 1;
  for (auto c : str)
    if ('0' <= c && c <= '9') {
      mode *= 10;
      mode += c - '0';
    }
  auto pos = str.find('.');
  if (pos != std::string::npos)
    for (size_t i = 1; i < str.size() - pos; i++)
      deno *= 10;
  contract();
}

int frac::get_mode(void) { return mode; }

int frac::get_deno(void) { return deno; }

double frac::calc(void) const { return (double)mode / deno; }

std::string frac::calc_str(size_t digit) const {
  std::string ret = "";
  auto tmp = mode;
  bool flag = true;
  while (ret.size() < digit + 1) {
    ret += std::to_string(tmp / deno);
    tmp %= deno;
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

frac frac::operator+(int num) const {
  frac ret(*this);
  ret += num;
  return ret;
}

frac frac::operator+(frac _frac) const {
  frac ret(*this);
  ret += _frac;
  return ret;
}

frac frac::operator-(int num) const {
  frac ret(*this);
  ret -= num;
  return ret;
}

frac frac::operator-(frac _frac) const {
  frac ret(*this);
  ret -= _frac;
  return ret;
}

frac frac::operator*(int num) const {
  frac ret(*this);
  ret *= num;
  return ret;
}

frac frac::operator*(frac _frac) const {
  frac ret(*this);
  ret *= _frac;
  return ret;
}

frac frac::operator/(int num) const {
  frac ret(*this);
  ret /= num;
  return ret;
}

frac frac::operator/(frac _frac) const {
  frac ret(*this);
  ret /= _frac;
  return ret;
}

void frac::operator+=(int num) {
  mode += num * deno;
  contract();
}

void frac::operator+=(frac _frac) {
  auto lcm = std::lcm(deno, _frac.deno);
  mode *= lcm / deno;
  mode += _frac.mode * (lcm / _frac.deno);
  deno = lcm;
  contract();
}

void frac::operator-=(int num) {
  mode -= num * deno;
  contract();
}
void frac::operator-=(frac _frac) {
  auto lcm = std::lcm(deno, _frac.deno);
  mode *= lcm / deno;
  mode -= _frac.mode * (lcm / _frac.deno);
  deno = lcm;
  contract();
}

void frac::operator*=(int num) {
  mode *= num;
  contract();
}

void frac::operator*=(frac _frac) {
  mode *= _frac.mode;
  deno *= _frac.deno;
  contract();
}

void frac::operator/=(int num) {
  deno *= num;
  contract();
}

void frac::operator/=(frac _frac) {
  mode *= _frac.deno;
  deno *= _frac.mode;
  contract();
}

bool frac::operator==(frac _frac) const {
  return mode == _frac.mode && deno == _frac.deno;
}

void frac::contract(void) {
  auto gcd = std::gcd(mode, deno);
  mode /= gcd;
  deno /= gcd;
}
