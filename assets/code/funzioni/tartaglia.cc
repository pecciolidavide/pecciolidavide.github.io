
#include <iostream>

#if false
// soluzione imperfetta
int bin(int n, int k) {
  int a = 1;
  for (int i = 1; i <= n; i++)
    a = a * i;
  int b = 1;
  for (int i = 1; i <= k; i++)
    b = b * i;
  int c = 1;
  for (int i = 1; i <= n - k; i++)
    c = c * i;
  return a / (b * c);
}
#endif

int fact(int n) {
  return n == 0 ? 1 : n * fact(n - 1);
}

int bin(int n, int k) {
  return fact(n) / (fact(n - k) * fact(k));
}

int main() {
  for (int n = 0; n < 10; n++) {
    for (int k = 0; k <= n; k++)
      std::cout << bin(n, k) << " ";
    std::cout << std::endl;
  }
}
