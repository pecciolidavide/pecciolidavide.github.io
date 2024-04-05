
#include "svg.hh"

int main() {
  SVG g(200, 200, 100, 100, std::cout);
  g.set_stroke("blue");
  g.set_stroke_width(1);
  for (int i = 0; i <= 10; i++) {
    g.line(i * 10, 0, 0, 100 - i * 10);
    g.line(i * 10, 0, 0, -100 + i * 10);
    g.line(-i * 10, 0, 0, 100 - i * 10);
    g.line(-i * 10, 0, 0, -100 + i * 10);
  }
}

