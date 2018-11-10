#pragma once
#include "BaseWindow.h"

namespace scgb{
  class BMimage :public BaseWindow{
  protected:
    std::vector<int> Pixels;
  public:
    void Draw(int x,int y);
    BMimage(std::string);
  };
}
