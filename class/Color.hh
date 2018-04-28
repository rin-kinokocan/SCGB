#pragma once
#include <ncurses.h>
#include <iostream>
#include <memory>

namespace scgb{
  class Color{
  public:
    Color();
    static int GetWebSafeColor(unsigned char r,unsigned char g,unsigned char b);
  };

  typedef std::unique_ptr<Color> Palette;
}
