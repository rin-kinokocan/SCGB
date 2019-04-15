#pragma once
#include "DrawingComponent.hpp"

namespace scgb{
  class Text:public DrawingComponent{
  protected:
    std::wstring text=L"default";
    attr_t attr=0;
  public:
    void Draw(){
      InitDraw();
      AddStr(text,attr);
    }
    void SetText(std::wstring str){
      text=str;
    }
    void SetAttr(attr_t a){
      attr=a;
    }
  };
}
