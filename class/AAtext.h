#pragma once
#include "BaseWindow.h"

namespace scgb{
  class AAtext :public BaseWindow{
  protected:
    std::vector<wchar_t> data;
  public:
    void Draw();
    AAtext(double x,double y,std::string filename);
  };
}
