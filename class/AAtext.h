#pragma once
#include "BaseWindow.h"
#include "Movable.hh"

namespace scgb{
  class AAtext :public Movable{
  protected:
    std::vector<wchar_t> data;
  public:
    void Draw();
    AAtext(int x,int y,std::string filename);
    ~AAtext();
  };
}
