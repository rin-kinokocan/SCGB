#pragma once
#include "WindowContainer.h"

namespace scgb{
  class InputBox:public WindowContainer{
  private:
    int x,y,w,h;
    std::vector<cChar> info;
  public:
    void Draw();
    InputBox(double,double,int,int,std::string);
  };
}
