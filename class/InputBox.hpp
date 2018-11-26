#pragma once
#include "ELHandler.hpp"
#include "WindowContainer.hpp"

namespace scgb{
  class InputBox:public WindowContainer,public ELHandler{
  protected:
    using WindowContainer::AddDC;
    std::wstring input;
  public:
    void StartInput();
    std::wstring GetInput(int maxch);
    void ChangeTitle(std::wstring title);
    InputBox(attr_t attr,int x,int y,int w,int h);
  };
}
