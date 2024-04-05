
// SOLUZIONE ESERCIZI 2 E 3

#include <iostream>
#include <utility>

template <typename T, typename S>
std::ostream& operator<<(std::ostream& os, const std::pair<T,S>& p) {
  os << "(" << p.first << "," << p.second << ")";
  return os;
}

#include "vector_template.hh"

template <typename T, typename S, int N>
Vector<std::pair<T,S>,N> zip(const Vector<T,N>& a,
			     const Vector<S,N>& b) {
  Vector<std::pair<T,S>,N> res;
  for (int i = 0; i < N; i++)
    res[i] = std::pair<T,S>(a[i], b[i]);
  return res;
}

template <typename T, typename S, int N>
std::pair< Vector<T,N>,Vector<S,N> > unzip(const Vector<std::pair<T,S>,N>& v) {
  Vector<T,N> a;
  Vector<S,N> b;
  for (int i = 0; i < N; i++) {
    a[i] = v[i].first;
    b[i] = v[i].second;
  }
  return std::pair<Vector<T,N>,Vector<S,N> >(a,b);
}


int main() {
  Vector<int,26> a;
  Vector<char,26> b;
  for (int i = 0; i < 26; i++) {
    a[i] = i;
    b[i] = (char) (i + 'a');
  }
  std::cout << zip(a, b) << std::endl;
  std::cout << unzip(zip(a, b)) << std::endl;
}
