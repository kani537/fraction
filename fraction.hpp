#include <numeric>
#include <string>
#include <utility>

class frac {
 public:
  explicit frac(int numerator = 0) : top(numerator), bottom(1) { contract(); }
  explicit frac(int numerator, int denominator) : top(numerator), bottom(denominator) { contract(); }
  explicit frac(double _double);
  explicit frac(std::pair<int, int> _pair) : top(_pair.first), bottom(_pair.second) { contract(); }
  explicit frac(const std::string &str);

  int get_top(void);
  int get_bottom(void);
  double calc(void) const;
  std::string calc_str(size_t digit = 10) const;

  inline frac operator+(const frac &_frac) const;
  inline frac operator-() const;
  inline frac operator-(const frac &_frac) const;
  inline frac operator*(const frac &_frac) const;
  inline frac operator/(const frac &_frac) const;

  inline void operator+=(const frac &_frac);
  inline void operator-=(const frac &_frac);
  inline void operator*=(const frac &_frac);
  inline void operator/=(const frac &_frac);
  inline bool operator==(const frac &_frac) const;
  inline bool operator!=(const frac &_frac) const;
  inline bool operator<(const frac &_frac) const;
  inline bool operator<=(const frac &_frac) const;
  inline bool operator>(const frac &_frac) const;
  inline bool operator>=(const frac &_frac) const;

 private:
  int64_t top;
  int64_t bottom;
  void contract(void);
};
