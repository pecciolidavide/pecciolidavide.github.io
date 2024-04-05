
#include "svg.hh"

int main() {
  SVG g(100, 100, 0, 0, std::cout);
  g.set_stroke("green");
  g.set_stroke_width(4);
  g.set_fill("yellow");
  g.circle(50, 50, 40);
}
