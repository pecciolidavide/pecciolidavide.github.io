
#include <iostream>
#include <vector>
#include <list>
#include <ctime>

class Set {
private:
  std::list<int> data; // invariante: lista ordinata
public:
  int size() const { return data.size(); }
  // SOLUZIONE ESERCIZIO 1
  bool empty() const { return size() == 0; }
  std::vector<int> elements() const;
  int minimum() const;
  int maximum() const;
  Set _union(const Set&) const;
  Set intersection(const Set&) const;
  Set difference(const Set&) const;
  bool contains(int) const;
  void insert(int);
  void remove(int);
  bool overlap(const Set&) const;
  friend std::ostream& operator<<(std::ostream&, const Set&);
};

bool Set::contains(int x) const {
  std::list<int>::const_iterator it = data.begin();
  while (it != data.end() && *it < x) it++;
  return it != data.end() && *it == x;
}

// SOLUZIONE ESERCIZIO 2
std::vector<int> Set::elements() const {
  std::vector<int> r;
  for (std::list<int>::const_iterator it = data.begin(); it != data.end(); it++)
    r.push_back(*it);
  // Restituisco r per valore poiché r è creato all'interno di questo metodo
  return r;
}

// SOLUZIONE ESERCIZIO 3
int Set::minimum() const {
  if (empty()) throw std::domain_error("empty set");
  // siccome data è ordinata, l'elemento più piccolo è il primo
  return *data.begin();
}

// SOLUZIONE ESERCIZIO 3
int Set::maximum() const {
  if (empty()) throw std::domain_error("empty set");
  // siccome data è ordinata, l'elemento più grande è l'ultimo
  std::list<int>::const_iterator it = data.end();
  it--;
  return *it;
}

void Set::insert(int x) {
  std::list<int>::iterator it = data.begin();
  while (it != data.end() && *it < x) it++;
  if (it == data.end() || *it != x) data.insert(it, x);
}

void Set::remove(int x) {
  std::list<int>::iterator it = data.begin();
  while (it != data.end() && *it < x) it++;
  if (it != data.end()) data.erase(it);
}

// SOLUZIONE ESERCIZIO 4
Set Set::_union(const Set& s) const {
  Set r;
  for (std::list<int>::const_iterator it = data.begin(); it != data.end(); it++)
    r.insert(*it);
  for (std::list<int>::const_iterator it = s.data.begin(); it != s.data.end(); it++)
    r.insert(*it);
  return r;
}

Set Set::intersection(const Set& s) const {
  Set r;
  for (std::list<int>::const_iterator it = data.begin(); it != data.end(); it++)
    if (s.contains(*it)) r.insert(*it);
  return r;
}

Set Set::difference(const Set& s) const {
  Set r;
  for (std::list<int>::const_iterator it = data.begin(); it != data.end(); it++)
    if (!s.contains(*it)) r.insert(*it);
  return r;
}
// FINE SOLUZIONE ESERCIZIO 4

// SOLUZIONE ESERCIZIO 5
bool Set::overlap(const Set& s) const {
  // faccio una scansione "parallela" dei due insiemi, faendo
  // avanzare l'iteratore che indica l'elemento più piccolo
  std::list<int>::const_iterator it = data.begin();
  std::list<int>::const_iterator sit = s.data.begin();
  while (it != data.end() && sit != s.data.end() && *it != *sit)
    if (*it < *sit) it++; else sit++;
  return it != data.end() && sit != s.data.end();
}

std::ostream& operator<<(std::ostream& os, const Set& s) {
  os << "{";
  std::list<int>::const_iterator it = s.data.begin();
  while (it != s.data.end()) {
    os << *it;
    it++;
    if (it != s.data.end()) std::cout << ",";
  }
  os << "}";
  return os;
}

Set create_random_set() {
  Set s;
  for (int i = 0; i < 5; i++)
    s.insert(std::rand() % 10);
  return s;
}

int main() {
  std::srand(std::time(nullptr));
  Set s1 = create_random_set();
  Set s2 = create_random_set();
  std::cout << "S1 = " << s1 << std::endl
	    << "S2 = " << s2 << std::endl
	    << "S1 ∪ S2 = " << s1._union(s2) << std::endl
	    << "S1 ∩ S2 = " << s1.intersection(s2) << std::endl
	    << "S1 \\ S2 = " << s1.difference(s2) << std::endl
	    << "S1 # S2 = " << s1.overlap(s2) << std::endl;
}
