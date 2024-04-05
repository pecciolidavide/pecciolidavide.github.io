
// SOLUZIONE DELL'ESERCIZIO 2

#include <iostream>
#include <vector>
#include <cmath>

class Vector {
private:
  std::vector<int> data;

public:
  Vector(int);
  int size() const;
  int operator[](int) const;
  int& operator[](int);
  Vector add(const Vector&) const;
  Vector sub(const Vector&) const;
  Vector mul(int) const;
  int mul(const Vector&) const;
};

Vector::Vector(int n) {
  if (n < 0) throw std::domain_error("invalid vector size");
  data.resize(n, 0);
}

int Vector::size() const {
  return data.size();
}

int Vector::operator[](int i) const {
  return data.at(i);
}

int& Vector::operator[](int i) {
  return data.at(i);
}

Vector Vector::add(const Vector& v) const {
  if (size() != v.size())
    throw std::domain_error("invalid size");
  Vector res(size());
  for (int i = 0; i < size(); i++)
    res[i] = data[i] + v[i];
  return res;
}

Vector Vector::sub(const Vector& v) const {
  return add(v.mul(-1));
}

Vector Vector::mul(int x) const {
  Vector res(size());
  for (int i = 0; i < size(); i++)
    res[i] = data[i] * x;
  return res;
}

int Vector::mul(const Vector& v) const {
  if (size() != v.size())
    throw std::domain_error("invalid size");
  int res = 0;
  for (int i = 0; i < size(); i++)
    res += data[i] * v[i];
  return res;
}

std::ostream& operator<<(std::ostream& os, const Vector& v) {
  os << "[";
  for (int i = 0; i < v.size(); i++)
    os << " " << v[i];
  os << " ]";
  return os;
}

int main() {
  Vector v(2);
  Vector w(2);
  v[0] = 1;
  v[1] = 2;
  w[0] = 3;
  w[1] = 4;
  std::cout << v << " + " << w << " = " << v.add(w) << std::endl;
  std::cout << v << " - " << w << " = " << v.sub(w) << std::endl;
  std::cout << v << " * " << w << " = " << v.mul(w) << std::endl;
  std::cout << std::sqrt(v.mul(v)) << std::endl;
}
