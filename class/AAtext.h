#pragma once
#include "BaseWindow.h"

namespace scgb{
  class AAtext :public BaseWindow{
  protected:
    std::vector<wchar_t> data;
  public:
    void Draw();
    AAtext(int x,int y,std::string filename);
  };
}
