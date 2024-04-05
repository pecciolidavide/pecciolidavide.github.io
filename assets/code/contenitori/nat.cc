
#include <iostream>
#include <iomanip>
#include <vector>

const int K = 4;
const int B = 10000; // B = 10^K

class nat {
private:
  std::vector<int> data; // ogni elemento è >= 0 e < B
  nat mul(int) const;
public:
  nat(int = 0);
  int size() const { return data.size(); }
  int digit(int) const;
  nat add(const nat&) const;
  nat mul(const nat&) const;
};

nat::nat(int n) {
  if (n < 0) throw std::domain_error("negative int");
  while (n > 0) {
    data.push_back(n % B);
    n /= B;
  }
}

int nat::digit(int i) const {
  if (i < 0) throw std::domain_error("negative index");
  return i < data.size() ? data[i] : 0;
}

nat nat::add(const nat& n) const {
  nat r;
  int carry = 0;
  for (int i = 0; i < size() || i < n.size(); i++) {
    int k = digit(i) + n.digit(i) + carry;
    r.data.push_back(k % B);
    carry = k / B;
  }
  if (carry != 0) r.data.push_back(carry);
  return r;
}

nat nat::mul(int n) const {
  if (n < 0 || n > B) throw std::domain_error("multiplier out of range");
  nat r;
  int carry = 0;
  for (int i = 0; i < size(); i++) {
    int k = data[i] * n + carry;
    r.data.push_back(k % B);
    carry = k / B;
  }
  if (carry != 0) r.data.push_back(carry);
  return r;
}

nat nat::mul(const nat& n) const {
  nat r;
  for (int i = n.size() - 1; i >= 0; i--)
    r = r.mul(B).add(this->mul(n.data[i]));
  return r;
}

nat operator+(const nat& m, const nat& n) {
  return m.add(n);
}

nat operator*(const nat& m, const nat& n) {
  return m.size() < n.size() ? n.mul(m) : m.mul(n);
}

#if false
std::ostream& operator<<(std::ostream& os, const nat& n) {
  if (n.size() == 0) os << "0";
  else
    for (int i = n.size() - 1; i >= 0; i--)
      os << n.digit(i);
  return os;
}
#else
std::ostream& operator<<(std::ostream& os, const nat& n) {
  if (n.size() == 0)
    os << std::setw(K) << std::setfill('0') << "0";
  else {
    os << n.digit(n.size() - 1);
    for (int i = n.size() - 2; i >= 0; i--)
      os << std::setw(K) << std::setfill('0') << n.digit(i);
  }
  return os;
}
#endif

nat fact(int n) {
  return n == 0 ? nat(1) : nat(n) * fact(n - 1);
}

int main() {
  std::cout << fact(10000) << std::endl;
}
