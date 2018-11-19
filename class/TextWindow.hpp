#pragma once
#include "WindowContainer.hpp"
#include "Border.hpp"
#include "DrawText.hpp"
namespace scgb{
  class TextWindow:public WindowContainer{
  private:
    using WindowContainer::AddDC;
  public:
    TextWindow(attr_t a,int x,int y,int w,int h):WindowContainer(x,y){
      AddDC(0,new Border(a,w,h));
      AddDC(1,new DrawText(a,w,h));
    }
    void ChangeText(std::wstring str){
      auto dt=GetDC<DrawText>(1);
      dt->ChangeText(str);
    }
  };
}
