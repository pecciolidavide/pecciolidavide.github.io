
#include <iostream>
#include <fstream>

int main() {
  std::ifstream is("numeri.txt");
  int s = 0;
  int n;
  while (is >> n) s += n;
  std::cout << "Somma = " << s << std::endl;
}
