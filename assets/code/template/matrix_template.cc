
#include "matrix_template.hh"

int main() {
  Matrix<int,2,3> a;
  a[0][0] = 2; a[0][1] = 1; a[0][2] = 4;
  a[1][0] = 0; a[1][1] = 1; a[1][2] = 1;

  Matrix<int,3,4> b;
  b[0][0] =  6; b[0][1] = 3; b[0][2] = -1; b[0][3] = 0;
  b[1][0] =  1; b[1][1] = 1; b[1][2] =  0; b[1][3] = 4;
  b[2][0] = -2; b[2][1] = 5; b[2][2] =  0; b[2][3] = 2;

  std::cout << a << " × " << std::endl << b << " = " << std::endl << a.mul(b) << std::endl;

  Matrix<int,2,3> m;
  std::cout << "Dammi gli elementi della matrice 2 x 3 da trasporre" << std::endl;
  std::cin >> m;
  std::cout << m << std::endl << m.transpose() << std::endl;
}
