#include <numeric>
#include <string>
#include <utility>

class frac {
 public:
  frac(int modelcure = 0, int denominator = 1);
  frac(std::pair<int, int> _pair);
  frac(const std::string &str);

  int get_mode(void);
  int get_deno(void);
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
  bool operator<(frac _frac) const;
  bool operator<=(frac _frac) const;
  bool operator>(frac _frac) const;
  bool operator>=(frac _frac) const;

 private:
  int mode;
  int deno;
  void contract(void);
};
