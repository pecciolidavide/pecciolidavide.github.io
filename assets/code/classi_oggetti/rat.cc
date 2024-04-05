
// SOLUZIONE ESERCIZI 1 E 2

#include <cmath>
#include <iostream>

class rat {
private:
  int num;
  int den; // invariante di classe: den > 0

  void init(int, int);
  rat pow_nn(int) const;

public:
  rat(int, int = 1);
  rat(double, int);
  int get_num() const { return num; }
  int get_den() const { return den; }
  int to_int() const;
  double to_double() const;
  rat add(const rat&) const;
  rat neg() const;
  rat sub(const rat&) const;
  rat mul(const rat&) const;
  rat recip() const;
  rat div(const rat&) const;
  rat reduce() const;
  rat pow(int) const;
};

void rat::init(int a, int b) {
  if (b > 0) {
    num = a;
    den = b;
    // invariante di classe soddisfatto
  } else if (b < 0) {
    num = -a;
    den = -b;
    // invariante di classe soddisfatto
  } else
    throw std::domain_error("division by zero");
}

// SCOPO: inizializzare una istanza della classe e assicurarsi che
// l'invariante di classe sia soddisfatto
rat::rat(int a, int b) {
  init(a, b);
}

rat::rat(double a, int n) {
  int m = std::pow(10, n);
  init((int) (a * m), m);
}

int rat::to_int() const {
  return num / den;
}

double rat::to_double() const {
  return (double) num / den;
}

rat rat::add(const rat& b) const {
  return rat(num * b.den + b.num * den, den * b.den);
}

rat rat::neg() const {
  return rat(-num, den);
}

rat rat::sub(const rat& b) const {
  return add(b.neg());
}

rat rat::mul(const rat& b) const {
  return rat(num * b.num, den * b.den);
}

rat rat::recip() const {
  return rat(den, num);
}

rat rat::div(const rat& b) const {
  return mul(b.recip());
}

rat operator+(const rat& a, const rat& b) {
  return a.add(b);
}

rat operator-(const rat& a, const rat& b) {
  return a.sub(b);
}

std::ostream& operator<<(std::ostream& os, const rat& a) {
  if (a.get_den() == 1) os << a.get_num();
  else os << a.get_num() << " / " << a.get_den();
  return os;
}

// INIZIO SOLUZIONE DELL'ESERCIZIO 2

bool operator==(const rat& a, const rat& b) {
  return (a - b).get_num() == 0;
}

bool operator!=(const rat& a, const rat& b) {
  return !(a == b);
}

bool operator<(const rat& a, const rat& b) {
  return (a - b).get_num() < 0;
}

bool operator>(const rat& a, const rat& b) {
  return (a - b).get_num() > 0;
}

bool operator>=(const rat& a, const rat& b) {
  return (a - b).get_num() >= 0;
}

// FINE SOLUZIONE DELL'ESERCIZIO 2

// a >= 0, b > 0
int gcd(int a, int b) {
  return a == 0 ? b : gcd(b % a, a);
}

rat rat::reduce() const {
  int m = gcd(std::abs(num), den);
  return rat(num / m, den / m);
}

rat rat::pow_nn(int n) const {
  return n == 0 ? rat(1) : mul(pow_nn(n - 1));
}

rat rat::pow(int n) const {
  return n >= 0 ? pow_nn(n) : pow_nn(-n).recip();
}

#if false
void test() {
  rat a(1, 2);
  std::cout << a.num << std::endl; // ERRORE!
}
#endif

void test() {
  rat a(1, 2);
  std::cout << a.get_num() << std::endl; // OK!
}

int main() {
  rat a(1, 2);
  rat b(3, 4);
  std::cout << a + b << std::endl;
  std::cout << (a + b).pow(-3).reduce() << std::endl;
}
