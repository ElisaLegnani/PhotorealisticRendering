#ifndef _color_h_
#define _color_h_

class Color {

public:
  // Costruttori
  Color() {
    m_r = 0.0;
    m_g = 0.0;
    m_b = 0.0;
  }

  Color(float r, float g, float b) {
    m_r = r;
    m_g = g;
    m_b = b;
  }

  // Distruttori
  ~Color(){};

  // Metodi
  Color operator+(Color);
  Color operator-(Color);

  bool are_colors_close(Color, Color);
  bool are_close(float, float);

private:
  float m_r, m_g, m_b;
};

#endif