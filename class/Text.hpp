#pragma once
#include "BaseView.hpp"
#include "Attribute.hpp"
#include "String.hpp"

namespace scgb{
  class Text:public BaseView{
  protected:
    std::shared_ptr<Attribute> attribute;
    std::shared_ptr<String> text;
  public:
    void Draw(){
      InitDraw();
      AddStr(text->GetData(),attribute->GetData());
    }
    Text(WindowInfo wi,std::shared_ptr<Attribute> attr,std::shared_ptr<String> str)
      :BaseView(wi),attribute(attr),text(str){}
  };
}
