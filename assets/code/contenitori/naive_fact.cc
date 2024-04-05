#include <iostream>

double fact(int n) {
  return n == 0 ? 1 : n * fact(n - 1);
}

int main() {
  std::cout << INT_MAX << std::endl;
  std::cout << fact(10000) << std::endl;
}
