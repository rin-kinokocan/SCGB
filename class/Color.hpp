#pragma once
#include "define.hpp"

namespace scgb{
  class Color{
    //manages color palette
  private:
    static int colorpairs;
  public:
    static bool Init();
    static attr_t GetColorPair(RGBvalue& top,RGBvalue& back);
    static attr_t GetByBackGround(RGBvalue& rgb);
    static attr_t GetByForeGround(RGBvalue& rgb);
    static short GetColor(RGBvalue& rgb);
    static void SetColors();
  };
}
