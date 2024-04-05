
#include <iostream>
#include <cmath>

struct rat {
  int num;
  int den;
};

// b != 0
rat rational(int a, int b = 1) {
  if (b > 0) {
    rat r = { a, b };
    return r;
  } else if (b < 0) {
    rat r = { -a, -b };
    return r;
  } else
    throw std::domain_error("division by zero");
}

rat rational(double a, int n) {
  int m = std::pow(10, n);
  return rational((int) (a * m), m);
}

int to_int(const rat& r) {
  return r.num / r.den;
}

double to_double(const rat& r) {
  return (double) r.num / r.den;
}

rat add(const rat& a, const rat& b) {
  return rational(a.num * b.den + b.num * a.den, a.den * b.den);
}

rat operator+(const rat& a, const rat& b) {
  return add(a, b);
}

rat neg(const rat& a) {
  return rational(-a.num, a.den);
}

rat sub(const rat& a, const rat& b) {
  return add(a, neg(b));
}

rat mul(const rat& a, const rat& b) {
  return rational(a.num * b.num, a.den * b.den);
}

rat recip(const rat& a) {
  return rational(a.den, a.num);
}

rat div(const rat& a, const rat& b) {
  return mul(a, recip(b));
}

void print(const rat& a) {
  if (a.den == 1) std::cout << a.num;
  else std::cout << a.num << " / " << a.den;
  std::cout << std::endl;
}

// a >= 0, b > 0
int gcd(int a, int b) {
  return a == 0 ? b : gcd(b % a, a);
}

rat reduce(const rat& a) {
  int m = gcd(std::abs(a.num), a.den);
  return rational(a.num / m, a.den / m);
}

rat pow_nn(const rat& a, int n) {
  return n == 0 ? rational(1) : mul(a, pow_nn(a, n - 1));
}

rat pow(const rat& a, int n) {
  return n >= 0 ? pow_nn(a, n) : recip(pow_nn(a, -n));
}

int main() {
  rat a = rational(1, 2);
  rat b = rational(3, 4);
  rat e = rational(std::exp(1), 5);
  print(a);
  print(e);
  std::cout << to_int(e) << std::endl;
  std::cout << to_double(e) << std::endl;
  print(add(a, b));
  print(reduce(add(a, b)));
  print(reduce(e));
  print(pow(a, 10));
}
