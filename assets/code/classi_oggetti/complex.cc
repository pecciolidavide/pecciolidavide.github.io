
// SOLUZIONE ESERCIZIO 3

#include <cmath>
#include <iostream>

class Complex {
private:
  double real;
  double imag;

public:
  Complex(double = 0.0, double = 0.0);
  double get_real() const { return real; }
  double get_imag() const { return imag; }
  Complex add(const Complex&) const;
  Complex neg() const;
  Complex sub(const Complex&) const;
  Complex mul(const Complex&) const;
  Complex recip() const;
  Complex div(const Complex&) const;
  double mod() const;
  Complex conj() const;
};

Complex::Complex(double r, double i) : real(r), imag(i) { }

Complex Complex::add(const Complex& c) const {
  return Complex(real + c.real, imag + c.imag);
}

Complex Complex::neg() const {
  return Complex(-real, -imag);
}

Complex Complex::sub(const Complex& c) const {
  return add(c.neg());
}

Complex Complex::mul(const Complex& c) const {
  return Complex(real * c.real - imag * c.imag, real * c.imag + imag * c.real);
}

Complex Complex::recip() const {
  double d = real * real + imag * imag;
  if (d == 0) throw std::domain_error("division by zero");
  return Complex(real / d, -imag / d);
}

Complex Complex::div(const Complex& c) const {
  return mul(c.recip());
}

Complex Complex::conj() const {
  return Complex(real, -imag);
}

double Complex::mod() const {
  return std::sqrt(real * real + imag * imag);
}

Complex operator+(const Complex& a, const Complex& b) {
  return a.add(b);
}

Complex operator-(const Complex& a, const Complex& b) {
  return a.sub(b);
}

Complex operator*(const Complex& a, const Complex& b) {
  return a.mul(b);
}

Complex operator/(const Complex& a, const Complex& b) {
  return a.div(b);
}

std::ostream& operator<<(std::ostream& os, const Complex& c) {
  os << c.get_real();
  if (c.get_imag() > 0.0) os << "+";
  if (c.get_imag() != 0.0) os << c.get_imag() << "i";
  return os;
}

int main() {
  Complex zero;
  Complex one(1.0);
  Complex a(1, -2);
  Complex b(1, 2);
  std::cout << "a     = " << a << std::endl
	    << "b     = " << b << std::endl
	    << "a + b = " << a + b << std::endl
	    << "a - b = " << a - b << std::endl
	    << "a * b = " << a * b << std::endl
	    << "a / b = " << a / b << std::endl;
}
