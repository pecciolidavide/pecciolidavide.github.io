
#include "vector_template.hh"

int main() {
  Vector<float,2> v;
  Vector<float,2> w;
  v[0] = 1;
  v[1] = 2;
  w[0] = 3;
  w[1] = 4;
  std::cout << v << " + " << w << " = " << v.add(w) << std::endl;
  std::cout << v << " - " << w << " = " << v.sub(w) << std::endl;
  std::cout << v << " * " << w << " = " << v.mul(w) << std::endl;
  std::cout << std::sqrt(v.mul(v)) << std::endl;
  Vector<float,4> z = append(v, w);
  std::cout << v << " ++ " << w << " = " << z << std::endl;
}
