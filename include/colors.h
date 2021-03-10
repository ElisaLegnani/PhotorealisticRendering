#ifndef _colors_h_
#define _colors_h_

class Colors {

public:
  // Costruttori
  Colors() {
    m_r = 0.0;
    m_g = 0.0;
    m_b = 0.0;
  }

  Colors(float r, float g, float b) {
    m_r = r;
    m_g = g;
    m_b = b;
  }

  // Distruttori
  ~Colors();

private:
  float m_r, m_g, m_b;
};

#endif
