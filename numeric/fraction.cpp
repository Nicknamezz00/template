template<typename T>
class Fraction {
 public:
  T num;
  T den;
  Fraction(T _num, T _den) : num(_num), den(_den) {
    if (den < 0) {
      den = -den;
      num = -num;
    }
  }
  Fraction() : Fraction(0, 1) {}
  Fraction(T _num) : Fraction(_num, 1) {}
  double toDouble() const {
    return 1.0 * num / den;
  }
  Fraction &operator+=(const Fraction &rhs) {
    num = num * rhs.den + rhs.num * den;
    den *= rhs.den;
    return *this;
  }
  Fraction &operator-=(const Fraction &rhs) {
    num = num * rhs.den - rhs.num * den;
    den *= rhs.den;
    return *this;
  }
  Fraction &operator*=(const Fraction &rhs) {
    num *= rhs.num;
    den *= rhs.den;
    return *this;
  }
  Fraction &operator/=(const Fraction &rhs) {
    num *= rhs.den;
    den *= rhs.num;
    if (den < 0) {
      num = -num;
      den = -den;
    }
    return *this;
  }
  friend Fraction operator+(Fraction lhs, const Fraction &rhs) {
    return lhs += rhs;
  }
  friend Fraction operator-(Fraction lhs, const Fraction &rhs) {
    return lhs -= rhs;
  }
  friend Fraction operator*(Fraction lhs, const Fraction &rhs) {
    return lhs *= rhs;
  }
  friend Fraction operator/(Fraction lhs, const Fraction &rhs) {
    return lhs /= rhs;
  }
  friend Fraction operator-(const Fraction &a) {
    return Fraction(-a.num, a.den);
  }
  friend bool operator==(const Fraction &lhs, const Fraction &rhs) {
    return lhs.num * rhs.den == rhs.num * lhs.den;
  }
  friend bool operator!=(const Fraction &lhs, const Fraction &rhs) {
    return lhs.num * rhs.den != rhs.num * lhs.den;
  }
  friend bool operator<(const Fraction &lhs, const Fraction &rhs) {
    return lhs.num * rhs.den < rhs.num * lhs.den;
  }
  friend bool operator>(const Fraction &lhs, const Fraction &rhs) {
    return lhs.num * rhs.den > rhs.num * lhs.den;
  }
  friend bool operator<=(const Fraction &lhs, const Fraction &rhs) {
    return lhs.num * rhs.den <= rhs.num * lhs.den;
  }
  friend bool operator>=(const Fraction &lhs, const Fraction &rhs) {
    return lhs.num * rhs.den >= rhs.num * lhs.den;
  }
};
