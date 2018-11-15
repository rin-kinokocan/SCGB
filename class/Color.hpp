#pragma once
#include <ncurses.h>
#include <iostream>
#include <memory>

namespace scgb{
  class Color{
  private:
    static int delta;
    static int phase;
  public:
    static void Init();
    static int GetColor(unsigned char r,unsigned char g,unsigned char b);
  };

  typedef std::unique_ptr<Color> Palette;
}
