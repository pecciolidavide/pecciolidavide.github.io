
#include <iostream>

// SOLUZIONE DELL'ESERCIZIO 2

class Jar {
private:
  int  capacity; // 0 <= capacity
  int  level;    // 0 <= level <= capacity
  bool _open;
public:
  Jar(int);
  void open()               { _open = true; }
  void close()              { _open = false; }
  bool is_open() const      { return _open; }
  void empty();
  void fill();
  void pour_into(Jar&);
  int  get_level() const    { return level; }
  int  get_capacity() const { return capacity; }
};

Jar::Jar(int c) {
  if (c < 0) throw std::domain_error("invalid capacity");
  capacity = c;
  level = 0;
  _open = false;
}

void Jar::empty() {
  if (is_open()) level = 0;
}

void Jar::fill() {
  if (is_open()) level = capacity;
}

void Jar::pour_into(Jar& b) {
  if (is_open() && b.is_open()) {
    int q = std::min(level, b.capacity - b.level);
    level -= q;
    b.level += q;
  }
}

int main() {
  Jar a(5);
  Jar b(3);
  a.open();
  b.open();
  b.fill();
  b.pour_into(a);
  b.fill();
  b.pour_into(a);
  a.empty();
  b.pour_into(a);
  b.fill();
  b.pour_into(a);
  std::cout << a.get_level() << std::endl;
}

// SOLUZIONE DELL'ESERCIZIO 1

void soluzione_alternativa() {
  Jar a(5);
  Jar b(3);
  a.open();
  b.open();
  a.fill();
  a.pour_into(b);
  b.empty();
  a.pour_into(b);
  a.fill();
  a.pour_into(b);
  std::cout << a.get_level() << std::endl;
}
