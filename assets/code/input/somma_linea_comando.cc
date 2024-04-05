
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
  int s = 0;
  for (int i = 1; i < argc; i++)
    s += std::stoi(argv[i]);
  std::cout << "Somma = " << s << std::endl;
}
