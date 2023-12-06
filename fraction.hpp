#include <numeric>
#include <string>
#include <utility>

class frac {
 public:
  frac(int numerator);
  frac(int numerator, int denominator);
  frac(std::pair<int, int> _pair);
  frac(const std::string &str);

  int get_top(void);
  int get_bottom(void);
  double calc(void) const;
  std::string calc_str(size_t digit = 10) const;

  frac operator+(frac _frac) const;
  frac operator-() const;
  frac operator-(frac _frac) const;
  frac operator*(frac _frac) const;
  frac operator/(frac _frac) const;

  void operator+=(frac _frac);
  void operator-=(frac _frac);
  void operator*=(frac _frac);
  void operator/=(frac _frac);
  bool operator==(frac _frac) const;
  bool operator!=(frac _frac) const;
  bool operator<(frac _frac) const;
  bool operator<=(frac _frac) const;
  bool operator>(frac _frac) const;
  bool operator>=(frac _frac) const;

 private:
  int top;
  int bottom;
  void contract(void);
};
