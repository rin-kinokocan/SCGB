#pragma once
#include "BaseWindow.h"

namespace scgb{
  class BMimage :public BaseWindow{
  protected:
    std::vector<int> Pixels;
  public:
    void Draw();
    BMimage(int,int,std::string);
  };
}
