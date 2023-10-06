#include <numeric>
#include <string>
#include <utility>

class fraction {
public:
  fraction(int modelcure = 0, int denominator = 1);
  fraction(std::pair<int, int> _pair);
  fraction(const std::string &str);

  int get_mode(void);
  int get_deno(void);
  double calc(void) const;

  fraction operator+(int num) const;
  fraction operator+(fraction _fraction) const;
  fraction operator-(int num) const;
  fraction operator-(fraction _fraction) const;
  fraction operator*(int num) const;
  fraction operator*(fraction _fraction) const;
  fraction operator/(int num) const;
  fraction operator/(fraction _fraction) const;

  void operator+=(int num);
  void operator+=(fraction _fraction);
  void operator-=(int num);
  void operator-=(fraction _fraction);
  void operator*=(int num);
  void operator*=(fraction _fraction);
  void operator/=(int num);
  void operator/=(fraction _fraction);
  bool operator==(fraction _fraction) const;

private:
  int mode;
  int deno;
  void contract(void);
};
