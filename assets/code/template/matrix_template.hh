
// SOLUZIONE ESERCIZIO 4

#ifndef __MATRIX_TEMPLATE_HH__
#define __MATRIX_TEMPLATE_HH__

#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>

#include "vector_template.hh"

template <typename T, int R, int C>
class Matrix {
public:
  typedef Vector<T,C> Row;
  typedef Vector<T,R> Column;

private:
  std::vector<Row> data;
  // R > 0
  // C > 0

public:
  Matrix();
  const Row& operator[](int i) const { return data.at(i); }
  Row& operator[](int i) { return data.at(i); }
  Column column(int) const;
  Matrix<T,C,R> transpose() const;
  Matrix<T,R,C> add(const Matrix<T,R,C>&) const;
  Matrix<T,R,C> neg() const;
  Matrix<T,R,C> sub(const Matrix<T,R,C>&) const;
  Matrix<T,R,C> mul(int) const;
  template <int K>
  Matrix<T,R,K> mul(const Matrix<T,C,K>&) const;
  int digits() const;
};

template <typename T, int R, int C>
Matrix<T,R,C>::Matrix() {
  if (R < 0 || C < 0) throw std::domain_error("invalid matrix size");
  data.resize(R, Row());
}

template <typename T, int R, int C>
Vector<T,R> Matrix<T,R,C>::column(int j) const {
  Column col;
  for (int i = 0; i < R; i++)
    col[i] = data[i][j];
  return col;
}

template <typename T, int R, int C>
Matrix<T,C,R> Matrix<T,R,C>::transpose() const {
  Matrix<T,C,R> m;
  for (int i = 0; i < R; i++)
    for (int j = 0; j < C; j++)
      m[j][i] = data[i][j];
  return m;
}

template <typename T, int R, int C>
Matrix<T,R,C> Matrix<T,R,C>::add(const Matrix<T,R,C>& m) const {
  Matrix<T,R,C> res;
  for (int i = 0; i < R; i++)
    res[i] = data[i].add(m[i]);
  return res;
}

template <typename T, int R, int C>
Matrix<T,R,C> Matrix<T,R,C>::mul(int x) const {
  Matrix<T,R,C> res;
  for (int i = 0; i < R; i++)
    res[i] = data[i].mul(x);
  return res;
}

template <typename T, int R, int C>
Matrix<T,R,C> Matrix<T,R,C>::sub(const Matrix<T,R,C>& m) const {
  return add(m.mul(-1));
}

template <typename T, int R, int C>
template <int K>
Matrix<T,R,K> Matrix<T,R,C>::mul(const Matrix<T,C,K>& m) const {
  Matrix<T,R,K> res;
  for (int i = 0; i < R; i++)
    for (int j = 0; j < K; j++)
      res[i][j] = data[i].mul(m.column(j));
  return res;
}

// IL SEGUENTE CODICE REALIZZA INPUT/OUTPUT DI MATRICI

template <typename T, int R, int C>
int Matrix<T,R,C>::digits() const {
  int d = 0;
  for (int i = 0; i < R; i++)
    for (int j = 0; j < C; j++) {
      int x = data[i][j];
      if (x == 0) d = std::max(d, 1);
      else if (x > 0) d = std::max(d, (int) std::log10(x) + 1);
      else d = std::max(d, (int) std::log10(-x) + 2);
    }
  return d;
}

template <typename T, int R, int C>
std::ostream& operator<<(std::ostream& os, const Matrix<T,R,C>& m) {
  int w = m.digits() + 1;
  for (int i = 0; i < R; i++) {
    if (R == 1) os << "(";
    else if (i == 0) os << "⎧";
    else if (i < R - 1) os << "⎪";
    else os << "⎩";

    for (int j = 0; j < C; j++)
      os << std::right << std::setw(w) << m[i][j];

    if (R == 1) os << " )";
    else if (i == 0) os << " ⎫" << std::endl;
    else if (i < R - 1) os << " ⎪" << std::endl;
    else os << " ⎭";
  }
  return os;
}

template <typename T, int R, int C>
std::istream& operator>>(std::istream& is, Matrix<T,R,C>& m) {
  for (int i = 0; i < R; i++)
    for (int j = 0; j < C; j++)
      is >> m[i][j];
  return is;
}

#endif // __MATRIX_TEMPLATE_HH__
