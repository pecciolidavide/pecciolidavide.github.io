
// SOLUZIONE ESERCIZIO 4: anche se la classe Time deve essere dotata
// di metodi per leggere ora, minuti e secondi individualmente, è
// comodo adottare come rappresentazione quella di un singolo numero
// intero, che rappresenta l'ora espressa in secondi. In tal modo,
// il metodo elapse si realizza facilmente. I metodi di accesso
// get_hour, get_mins, get_secs danno all'utilizzatore della classe
// l'impressione che tali quantità siano disponibili
// individualmente, quando invece le calcolano solo all'occorrenza.

#include <iostream>
#include <iomanip>

class Time {
private:
  int time; // 0 <= time < 24*3600

public:
  Time(int);
  Time(int, int, int);
  int get_hour() const { return time / 3600; }
  int get_mins() const { return (time % 3600) / 60; }
  int get_secs() const { return (time % 3600) % 60; }
  Time elapse(int) const;
};

Time::Time(int s) {
  if (s < 0) throw std::domain_error("negative time");
  time = s % (24 * 3600);
}

Time::Time(int h, int m, int s) {
  if (h < 0 || h > 23 || m < 0 || m > 59 || s < 0 || s > 59)
    throw std::domain_error("negative time");
  time = h * 3600 + m * 60 + s;
}

Time Time::elapse(int s) const {
  if (s < 0) throw std::domain_error("negative time");
  return Time(time + s);
}

std::ostream& operator<<(std::ostream& os, const Time& a) {
  os << std::setfill('0')
     << std::setw(2)
     << a.get_hour() << ":"
     << std::setfill('0')
     << std::setw(2)
     << a.get_mins() << ":"
     << std::setfill('0')
     << std::setw(2)
     << a.get_secs();
  return os;
}

int main() {
  Time a(86399);
  std::cout << a << std::endl << a.elapse(50000) << std::endl;
}
