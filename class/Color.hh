#pragma once
#include <ncurses.h>
#include <iostream>
#include <memory>

namespace scgb{
  class Color{
  public:
    static void Init();
    static int GetWebSafeColor(unsigned char r,unsigned char g,unsigned char b);
  };

  typedef std::unique_ptr<Color> Palette;
}
