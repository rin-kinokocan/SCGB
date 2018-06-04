#pragma once
#include "WindowContainer.h"

namespace scgb{
  class InputBox:public WindowContainer{
  private:
    int x,y,w,h;
  public:
    std::vector<cChar> info;
    int maxchar;
    void Draw();
    std::vector<wchar_t> GetInput();
    InputBox(int x,int y,int width,int height,int maxchar,std::string);
  };
}
