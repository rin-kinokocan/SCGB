#pragma once
#include "BaseWindow.h"

namespace scgb{
  class BMimage :public BaseWindow{
  protected:
    void ReadFile();
    File file;
    BMfile bf;
    BMinfo bi;
    std::vector<int> Pixels;
  public:
    void Draw();
    BMimage(int x,int y,const char* filename);
  };
}
