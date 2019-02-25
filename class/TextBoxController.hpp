#pragma once
#include "Color.hpp"
#include "BaseController.hpp"
#include "TextBox.hpp"

namespace scgb{
  class TextBoxController:public BaseController{
  private:
    std::unique_ptr<TextBox> textbox;
    std::shared_ptr<Attribute> attr;
    std::shared_ptr<String> text;
  public:
    void Draw(){
      textbox->Draw();
    }
    void SetText(std::wstring str){
      text->SetData(str);
    }
    TextBoxController(Geometry* geo,Coordinate* coord,RGBvalue &fg,RGBvalue &bg,std::wstring str=L"")
      :BaseController(geo,coord){
      text=std::make_shared<String>(str);
      this->attr=std::make_unique<Attribute>(Color::GetColorPair(fg,bg));
      this->textbox=std::make_unique<TextBox>(wi,attr,text);
    }
  };
}
