#pragma once
#include "BaseWindow.hpp"

namespace scgb{
  class BMimage :public BaseWindow{
  protected:
    std::vector<int> pixels;
  public:
    void Draw(int x,int y);
    BMimage(std::string);
  };
}
