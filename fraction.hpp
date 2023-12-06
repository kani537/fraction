#include <numeric>
#include <string>
#include <utility>

class frac {
 public:
  frac(int numerator) : top(numerator), bottom(1) { contract(); }
  frac(int numerator, int denominator) : top(numerator), bottom(denominator) { contract(); }
  frac(std::pair<int, int> _pair) : top(_pair.first), bottom(_pair.second) { contract(); }
  frac(const std::string &str);

  int get_top(void);
  int get_bottom(void);
  double calc(void) const;
  std::string calc_str(size_t digit = 10) const;

  frac operator+(const frac &_frac) const;
  frac operator-() const;
  frac operator-(const frac &_frac) const;
  frac operator*(const frac &_frac) const;
  frac operator/(const frac &_frac) const;

  void operator+=(const frac &_frac);
  void operator-=(const frac &_frac);
  void operator*=(const frac &_frac);
  void operator/=(const frac &_frac);
  bool operator==(const frac &_frac) const;
  bool operator!=(const frac &_frac) const;
  bool operator<(const frac &_frac) const;
  bool operator<=(const frac &_frac) const;
  bool operator>(const frac &_frac) const;
  bool operator>=(const frac &_frac) const;

 private:
  int top;
  int bottom;
  void contract(void);
};
