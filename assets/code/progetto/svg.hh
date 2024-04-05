
#ifndef __SVG_HH__
#define __SVG_HH__

#include <iostream>
#include <string>

class SVG {
private:
  std::ostream& os;

  int width;
  int height;
  int ox;
  int oy;
  std::string stroke; // color
  int stroke_width;
  std::string fill;   // filler color, or transparent

  void begin(const std::string&);
  void shape_attrs();
  void content(const std::string&);
  void end();
  void end(const std::string&);

  int tx(int x) const { return x + ox; }
  int ty(int y) const { return -y - oy + height; }
  template <typename T>
  void attr(const std::string& name, const T& value) {
    os << " " << name << "=\"" << value << "\"";
  }

public:
  SVG(int, int, int, int, std::ostream&);
  ~SVG();
  void set_stroke(const std::string& = "black");
  void set_stroke_width(int = 1);
  void set_fill(const std::string& = "transparent");
  void rect(int, int, int, int);
  void circle(int, int, int);
  void line(int, int, int, int);
  void text(int, int, const std::string&);
};

#endif // __SVG_HH__
