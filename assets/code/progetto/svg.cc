
#include "svg.hh"

SVG::SVG(int width, int height, int ox, int oy, std::ostream& os)
  : width(width), height(height), ox(ox), oy(oy), os(os) {
  os << "<?xml version=\"1.0\" standalone=\"no\"?>" << std::endl
     << "<svg version=\"1.1\" baseProfile=\"full\""
     << " width=\"" << width << "\""
     << " height=\"" << height << "\""
     << " xmlns=\"http://www.w3.org/2000/svg\">"
     << std::endl;
  set_stroke();
  set_stroke_width();
  set_fill();
}

SVG::~SVG() {
  os << "</svg>" << std::endl;
}

void SVG::begin(const std::string& tag) {
  os << "  <" << tag;
}

void SVG::end() {
  os << "/>" << std::endl;
}

void SVG::end(const std::string& tag) {
  os << "/" << tag << ">" << std::endl;
}

void SVG::content(const std::string& s) {
  os << ">" << s << "<";
}

void SVG::set_stroke(const std::string& s) {
  stroke = s;
}

void SVG::set_stroke_width(int w) {
  stroke_width = w;
}

void SVG::set_fill(const std::string& s) {
  fill = s;
}

void SVG::shape_attrs() {
  attr("stroke", stroke);
  attr("stroke-width", stroke_width);
  attr("fill", fill);
}

void SVG::line(int x1, int y1, int x2, int y2) {
  begin("line");
  attr("x1", tx(x1));
  attr("y1", ty(y1));
  attr("x2", tx(x2));
  attr("y2", ty(y2));
  shape_attrs();
  end();
}

void SVG::rect(int x, int y, int w, int h) {
  begin("rect");
  attr("x", tx(x));
  attr("y", ty(y + h));
  attr("width", w);
  attr("height", h);
  shape_attrs();
  end();
}

void SVG::circle(int x, int y, int r) {
  begin("circle");
  attr("cx", tx(x));
  attr("cy", ty(y));
  attr("r", r);
  shape_attrs();
  end();
}

void SVG::text(int x, int y, const std::string& s) {
  begin("text");
  attr("x", tx(x));
  attr("y", ty(y));
  attr("fill", fill);
  content(s);
  end("text");
}
