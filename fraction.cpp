#include "fraction.hpp"

fraction::fraction(int modelcure, int denominator) {
  mode = modelcure;
  deno = denominator;
  contract();
}

fraction::fraction(std::pair<int, int> _pair) {
  mode = _pair.first;
  deno = _pair.second;
  contract();
}

fraction::fraction(const std::string &str) {
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

int fraction::get_mode(void) { return mode; }

int fraction::get_deno(void) { return deno; }

double fraction::calc(void) const { return (double)mode / deno; }

fraction fraction::operator+(int num) const {
  fraction ret(*this);
  ret += num;
  return ret;
}

fraction fraction::operator+(fraction _fraction) const {
  fraction ret(*this);
  ret += _fraction;
  return ret;
}

fraction fraction::operator-(int num) const {
  fraction ret(*this);
  ret -= num;
  return ret;
}

fraction fraction::operator-(fraction _fraction) const {
  fraction ret(*this);
  ret -= _fraction;
  return ret;
}

fraction fraction::operator*(int num) const {
  fraction ret(*this);
  ret *= num;
  return ret;
}

fraction fraction::operator*(fraction _fraction) const {
  fraction ret(*this);
  ret *= _fraction;
  return ret;
}

fraction fraction::operator/(int num) const {
  fraction ret(*this);
  ret /= num;
  return ret;
}

fraction fraction::operator/(fraction _fraction) const {
  fraction ret(*this);
  ret /= _fraction;
  return ret;
}

void fraction::operator+=(int num) {
  mode += num * deno;
  contract();
}

void fraction::operator+=(fraction _fraction) {
  auto lcm = std::lcm(deno, _fraction.deno);
  mode *= lcm / deno;
  mode += _fraction.mode * (lcm / _fraction.deno);
  deno = lcm;
  contract();
}

void fraction::operator-=(int num) {
  mode -= num * deno;
  contract();
}
void fraction::operator-=(fraction _fraction) {
  auto lcm = std::lcm(deno, _fraction.deno);
  mode *= lcm / deno;
  mode -= _fraction.mode * (lcm / _fraction.deno);
  deno = lcm;
  contract();
}

void fraction::operator*=(int num) {
  mode *= num;
  contract();
}

void fraction::operator*=(fraction _fraction) {
  mode *= _fraction.mode;
  deno *= _fraction.deno;
  contract();
}

void fraction::operator/=(int num) {
  deno *= num;
  contract();
}

void fraction::operator/=(fraction _fraction) {
  mode *= _fraction.deno;
  deno *= _fraction.mode;
  contract();
}

bool fraction::operator==(fraction _fraction) const {
  return mode == _fraction.mode && deno == _fraction.deno;
}

void fraction::contract(void) {
  auto gcd = std::gcd(mode, deno);
  mode /= gcd;
  deno /= gcd;
}
