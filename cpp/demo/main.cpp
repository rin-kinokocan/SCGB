#include "scgb.hpp"
using namespace scgb;
using namespace scgb::Util;
int main(){
  GameWindow gw("ja_JP.UTF-8");
  InputMap im;
  Clock clock;
  RGBvalue fg(255,255,255);
  RGBvalue bg(0,0,255);
  auto text=std::make_shared<TextBoxController>(new Geometry(31,5),new Coordinate(3,10),fg,bg);
  gw.Append(text);
  text->SetText(L"Hay, there mortal! Give me back the jewel!");
  while(true){
    gw.Draw();
  }
  return 0;
}
