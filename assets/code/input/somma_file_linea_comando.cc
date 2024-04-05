
#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
  if (argc != 2) throw std::domain_error("nome del file mancante");
  std::ifstream is(argv[1]);
  int s = 0;
  int n;
  while (is >> n) s += n;
  std::cout << "Somma = " << s << std::endl;
}
