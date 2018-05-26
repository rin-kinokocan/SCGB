#pragma once
#include "define.h"
#include "WindowContainer.h"

namespace scgb{
  class InputBox:public WindowContainer{
  private:
    int x,y,w,h;
  public:
    std::string info;
    int maxchar;
    bool isActive=false;
    void Draw();
    void SetActive(bool);
    std::vector<wchar_t> GetInput();
    InputBox(int x,int y,int width,int height,int maxchar,std::string);
  };
}
