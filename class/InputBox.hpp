#pragma once
#include "ELHandler.hpp"
#include "WindowContainer.hpp"

namespace scgb{
  class InputBox:public WindowContainer,public ELHandler{
    //one line title + one line input.
  protected:
    using WindowContainer::AddDC;
    bool isStarted=false;
    int maxchar;
    std::wstring input;
  public:
    void Exec(InputMap);
    void StartInput();
    std::wstring GetInput(int maxch);
    void ChangeTitle(std::wstring title);
    InputBox(attr_t attr,int maxchar,int x,int y,int w,int h);
  };
}
