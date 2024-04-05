
// SOLUZIONE DELL'ESERCIZIO 3

#include <vector>
#include <iostream>
#include <iomanip>
#include <cmath>

// COPIO IL CODICE DI vector.cc QUI PER POTER RIUTILIZZARE I VETTORI
// DEFINITI IN PRECEDENZA.

class Vector {
private:
  std::vector<int> data;

public:
  Vector(int);
  int size() const;
  int operator[](int) const;
  int& operator[](int);
  Vector add(const Vector&) const;
  Vector sub(const Vector&) const;
  Vector mul(int) const;
  int mul(const Vector&) const;
};

Vector::Vector(int n) {
  if (n < 0) throw std::domain_error("invalid vector size");
  data.resize(n, 0);
}

int Vector::size() const {
  return data.size();
}

int Vector::operator[](int i) const {
  return data.at(i);
}

int& Vector::operator[](int i) {
  return data.at(i);
}

Vector Vector::add(const Vector& v) const {
  if (size() != v.size())
    throw std::domain_error("invalid size");
  Vector res(size());
  for (int i = 0; i < size(); i++)
    res[i] = data[i] + v[i];
  return res;
}

Vector Vector::sub(const Vector& v) const {
  return add(v.mul(-1));
}

Vector Vector::mul(int x) const {
  Vector res(size());
  for (int i = 0; i < size(); i++)
    res[i] = data[i] * x;
  return res;
}

int Vector::mul(const Vector& v) const {
  if (size() != v.size())
    throw std::domain_error("invalid size");
  int res = 0;
  for (int i = 0; i < size(); i++)
    res += data[i] * v[i];
  return res;
}

std::ostream& operator<<(std::ostream& os, const Vector& v) {
  os << "[";
  for (int i = 0; i < v.size(); i++)
    os << " " << v[i];
  os << " ]";
  return os;
}

class Matrix {
private:
  int n_rows; // n_rows >= 0
  int n_cols;
  std::vector<Vector> data;
  // n_rows > 0
  // n_cols > 0
  // data.size() == n_rows
  // ∀ 0 <= i < n_rows : data[i].size() == n_cols

public:
  Matrix(int, int);
  int get_rows() const { return n_rows; }
  int get_cols() const { return n_cols; }
  const Vector& operator[](int i) const { return data.at(i); }
  Vector& operator[](int i) { return data.at(i); }
  Vector column(int) const;
  Matrix transpose() const;
  Matrix add(const Matrix&) const;
  Matrix neg() const;
  Matrix sub(const Matrix&) const;
  Matrix mul(int) const;
  Matrix mul(const Matrix&) const;
  int digits() const;
};

Matrix::Matrix(int r, int c) {
  if (r < 0 || c < 0) throw std::domain_error("invalid matrix size");
  n_rows = r;
  n_cols = c;
  data.resize(r, Vector(c));
}

Vector Matrix::column(int j) const {
  Vector col(n_rows);
  for (int i = 0; i < n_rows; i++)
    col[i] = data[i][j];
  return col;
}

Matrix Matrix::transpose() const {
  Matrix m(n_cols, n_rows);
  for (int i = 0; i < n_rows; i++)
    for (int j = 0; j < n_cols; j++)
      m[j][i] = data[i][j];
  return m;
}

Matrix Matrix::add(const Matrix& m) const {
  if (get_rows() != m.get_rows() || get_cols() != m.get_cols())
    throw std::domain_error("invalid matrix size");
  Matrix res(n_rows, n_cols);
  for (int i = 0; i < n_rows; i++)
    res[i] = data[i].add(m[i]);
  return res;
}

Matrix Matrix::mul(int x) const {
  Matrix res(n_rows, n_cols);
  for (int i = 0; i < n_rows; i++)
    res[i] = data[i].mul(x);
  return res;
}

Matrix Matrix::sub(const Matrix& m) const {
  return add(m.mul(-1));
}

Matrix Matrix::mul(const Matrix& m) const {
  if (get_cols() != m.get_rows())
    throw std::domain_error("invalid matrix size");
  Matrix res(get_rows(), m.get_cols());
  for (int i = 0; i < get_rows(); i++)
    for (int j = 0; j < m.get_cols(); j++)
      res[i][j] = data[i].mul(m.column(j));
  return res;
}

// IL SEGUENTE CODICE REALIZZA INPUT/OUTPUT DI MATRICI

int Matrix::digits() const {
  int d = 0;
  for (int i = 0; i < n_rows; i++)
    for (int j = 0; j < n_cols; j++) {
      int x = data[i][j];
      if (x == 0) d = std::max(d, 1);
      else if (x > 0) d = std::max(d, (int) std::log10(x) + 1);
      else d = std::max(d, (int) std::log10(-x) + 2);
    }
  return d;
}

std::ostream& operator<<(std::ostream& os, const Matrix& m) {
  int w = m.digits() + 1;
  for (int i = 0; i < m.get_rows(); i++) {
    if (m.get_rows() == 1) os << "(";
    else if (i == 0) os << "⎧";
    else if (i < m.get_rows() - 1) os << "⎪";
    else os << "⎩";

    for (int j = 0; j < m.get_cols(); j++)
      os << std::right << std::setw(w) << m[i][j];

    if (m.get_rows() == 1) os << " )";
    else if (i == 0) os << " ⎫" << std::endl;
    else if (i < m.get_rows() - 1) os << " ⎪" << std::endl;
    else os << " ⎭";
  }
  return os;
}

std::istream& operator>>(std::istream& is, Matrix& m) {
  for (int i = 0; i < m.get_rows(); i++)
    for (int j = 0; j < m.get_cols(); j++)
      is >> m[i][j];
  return is;
}

int main() {
  Matrix a(2, 3);
  a[0][0] = 2; a[0][1] = 1; a[0][2] = 4;
  a[1][0] = 0; a[1][1] = 1; a[1][2] = 1;

  Matrix b(3, 4);
  b[0][0] =  6; b[0][1] = 3; b[0][2] = -1; b[0][3] = 0;
  b[1][0] =  1; b[1][1] = 1; b[1][2] =  0; b[1][3] = 4;
  b[2][0] = -2; b[2][1] = 5; b[2][2] =  0; b[2][3] = 2;

  std::cout << a << " × " << std::endl << b << " = " << std::endl << a.mul(b) << std::endl;

  int r, c;
  std::cout << "Dammi n. di righe e colonne della matrice da trasporre" << std::endl;
  std::cin >> r >> c;
  Matrix m(r, c);
  std::cout << "Dammi gli elementi della matrice da trasporre" << std::endl;
  std::cin >> m;
  std::cout << m << std::endl << m.transpose() << std::endl;
}
