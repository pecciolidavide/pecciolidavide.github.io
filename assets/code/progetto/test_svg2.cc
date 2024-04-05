
#include <cmath>
#include "svg.hh"

int main() {
  SVG g(1020, 520, 20, 20, std::cout);
  g.set_stroke("#E0E0E0");
  for (int i = 0; i < 50; i++) {
    if (i % 10 == 0) {
      g.set_fill("black");
      g.text(-20, i * 10, std::to_string(i));
    }
    for (int j = 0; j < 100; j++) {
      if (i == 0 && j % 10 == 0) {
	g.set_fill("black");
	g.text(j * 10, -20, std::to_string(j));
      }
      g.line(0, i * 10, 1000, i * 10);
      g.line(j * 10, 0, j * 10, 500);
    }
  }
  g.set_stroke("black");
  g.line(0, 0, 0, 500);
  g.line(0, 0, 1000, 0);
  g.set_fill("#00A000");
  for (int j = 0; j < 1000; j++) {
    g.circle(j, 250 + 0.2 * j * sin(j / 20.0), 2);
  }
}

