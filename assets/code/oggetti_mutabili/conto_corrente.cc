
// SOLUZIONE ESERCIZIO 3

#include <iostream>

class ContoCorrente {
private:
  int _saldo;
  int _max_saldo; // 0 <= saldo <= max_saldo

public:
  ContoCorrente();
  int saldo() const { return _saldo; }
  int max_saldo() const { return _max_saldo; }
  void versamento(int);
  void prelievo(int);
};

ContoCorrente::ContoCorrente() {
  _saldo = _max_saldo = 0;
}

void ContoCorrente::versamento(int x) {
  if (x < 0) throw std::domain_error("versamento negativo");
  _saldo += x;
  _max_saldo = std::max(_max_saldo, _saldo);
}

void ContoCorrente::prelievo(int x) {
  if (x < 0) throw std::domain_error("prelievo negativo");
  if (x > _saldo) throw std::domain_error("disponibilità insufficiente");
  _saldo -= x;
}

#if false
// VARIANTE IN CUI IL METODO "PRELIEVO" RESTITUISCE TRUE O FALSE A
// SECONDA CHE CI SIA DISPONIBILITÀ SUFFICIENTE O MENO

bool ContoCorrente::prelievo(int x) {
  if (x < 0) throw std::domain_error("prelievo negativo");
  if (x > _saldo)
    return false;
  else {
    _saldo -= x;
    return true;
  }
}
#endif

int main() {
  ContoCorrente c;
  c.versamento(1000);
  c.versamento(500);
  c.prelievo(60);
  std::cout << c.saldo() << std::endl << c.max_saldo() << std::endl;
}
