
#include <iostream>
#include <ctime>
#include <map>

class MultiSet {
private:
  std::map<int, int> data; // invariante: la seconda componente delle coppie è >= 0
public:
  int size() const;
  int operator[](int) const;
  void insert(int, int = 1);
  void remove(int, int = 1);
  MultiSet _union(const MultiSet&) const;
  friend std::ostream& operator<<(std::ostream&, const MultiSet&);
};

int MultiSet::size() const {
  int n = 0;
  for (std::map<int, int>::const_iterator it = data.begin(); it != data.end(); it++)
    n += it->second;
  return n;
}

int MultiSet::operator[](int x) const {
  std::map<int, int>::const_iterator it = data.find(x);
  return it != data.end() ? it->second : 0;
}

void MultiSet::insert(int x, int n) {
  if (n < 0) throw std::domain_error("negative multiplicity");
  data[x] += n;
}

void MultiSet::remove(int x, int n) {
  if (n < 0) throw std::domain_error("negative multiplicity");
  data[x] -= std::min(data[x], n);
}

MultiSet MultiSet::_union(const MultiSet& s) const {
  MultiSet r;
  for (std::map<int, int>::const_iterator it = data.begin(); it != data.end(); it++)
    r.insert(it->first, it->second);
  for (std::map<int, int>::const_iterator it = s.data.begin(); it != s.data.end(); it++)
    r.insert(it->first, it->second);
  return r;
}

std::ostream& operator<<(std::ostream& os, const MultiSet& s) {
  bool first = true;
  os << "{";
  std::map<int, int>::const_iterator it = s.data.begin();
  while (it != s.data.end()) {
    if (it->second > 0) {
      if (first) first = false; else os << ",";
      os << "(" << it->first << ", " << it->second << ")";
    }
    it++;
  }
  os << "}";
  return os;
}

MultiSet create_random_multiset() {
  MultiSet s;
  for (int i = 0; i < 5; i++)
    s.insert(std::rand() % 10);
  return s;
}

int main() {
  std::srand(std::time(nullptr));
  MultiSet s1 = create_random_multiset();
  MultiSet s2 = create_random_multiset();
  std::cout << "S1 = " << s1 << std::endl
	    << "S2 = " << s2 << std::endl
	    << "S1 ∪ S2 = " << s1._union(s2) << std::endl;
}
