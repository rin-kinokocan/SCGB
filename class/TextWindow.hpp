#pragma once
#include "WindowContainer.hpp"
#include "Border.hpp"
#include "TextWriter.hpp"

namespace scgb{
  class TextWindow:public WindowContainer{
  private:
    using WindowContainer::AddDC;
  public:
    TextWindow(std::wstring str,attr_t a,int x,int y,int w,int h):
      TextWindow(a,x,y,w,h){
      ChangeText(str);
    }
      
    TextWindow(attr_t a,int x,int y,int w,int h):WindowContainer(x,y){
      AddDC(0,new Border(a,w,h));
      AddDC(1,new TextWriter(a,w-2,h-2),1,1);
    }
    void ChangeText(std::wstring str){
      auto dt=GetDC<TextWriter>(1);
      dt->ChangeText(str);
    }
  };
}
