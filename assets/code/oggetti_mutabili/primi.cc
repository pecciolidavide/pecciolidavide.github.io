
#include <iostream>

class Primi {
private:
  int candidato;

  bool primo() const;

public:
  Primi();
  int next();
};

Primi::Primi() : candidato(2) { }

bool Primi::primo() const {
  for (int i = 2; i <= candidato / 2; i++)
    if (candidato % i == 0) return false;
  return true;
}

int Primi::next() {
  while (!primo()) candidato++;
  return candidato++;
}

int main() {
  Primi p;
  for (int i = 1; i <= 100; i++)
    std::cout << i << ") " << p.next() << std::endl;
}
