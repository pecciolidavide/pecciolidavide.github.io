
// SOLUZIONE ESERCIZIO 1 PIU` AVANTI NEL FILE

#ifndef __VECTOR_TEMPLATE_HH__
#define __VECTOR_TEMPLATE_HH__

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

template <typename T, int N>
class Vector {
private:
  std::vector<T> data;

public:
  Vector();
  T operator[](int) const;
  T& operator[](int);
  Vector<T,N> add(const Vector<T,N>&) const;
  Vector<T,N> sub(const Vector<T,N>&) const;
  Vector<T,N> mul(T) const;
  T mul(const Vector<T,N>&) const;
};

template <typename T, int N>
Vector<T,N>::Vector() {
  if (N < 0) throw std::domain_error("invalid vector size");
  data.resize(N, T());
}

template <typename T, int N>
T Vector<T,N>::operator[](int i) const {
  return data.at(i);
}

template <typename T, int N>
T& Vector<T,N>::operator[](int i) {
  return data.at(i);
}

template <typename T, int N>
Vector<T,N> Vector<T,N>::add(const Vector<T,N>& v) const {
  Vector<T,N> res;
  for (int i = 0; i < N; i++)
    res[i] = data[i] + v[i];
  return res;
}

// INIZIO SOLUZIONE ESERCIZIO 1

template <typename T, int N>
Vector<T,N> Vector<T,N>::sub(const Vector<T,N>& v) const {
  return add(v.mul(-1));
}

template <typename T, int N>
Vector<T,N> Vector<T,N>::mul(T x) const {
  Vector<T,N> res;
  for (int i = 0; i < N; i++)
    res[i] = data[i] * x;
  return res;
}

template <typename T, int N>
T Vector<T,N>::mul(const Vector<T,N>& v) const {
  T res = T(); // lo zero di tipo T
  for (int i = 0; i < N; i++)
    res += data[i] * v[i];
  return res;
}

// Vincoli aggiuntivi: deve essere possibile moltiplicare con *
// elementi di tipo T

// FINE SOLUZIONE ESERCIZIO 1

template <typename T, int N, int M>
Vector<T,N+M> append(const Vector<T,N>& a,
		     const Vector<T,M>& b) {
  Vector<T,N+M> c;
  for (int i = 0; i < N; i++) c[i] = a[i];
  for (int i = 0; i < M; i++) c[i + N] = b[i];
  return c;
}

template <typename T, int N>
std::ostream& operator<<(std::ostream& os, const Vector<T,N>& v) {
  os << "[";
  for (int i = 0; i < N; i++)
    os << " " << v[i];
  os << " ]";
  return os;
}

#endif // __VECTOR_TEMPLATE_HH__
