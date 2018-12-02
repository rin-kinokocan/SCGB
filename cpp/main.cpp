#include "scgb.hpp"
using namespace scgb;
using namespace scgb::Util;
int main(){
  GameWindow gw("ja_JP.UTF-8");
  GWEventListner gel;
  IBEventListner iel;
  InputMap im;
  Clock clock;
  RGBvalue tw_top(255,255,255);
  RGBvalue tw_back(0,0,255);
  auto wincolor=Color::GetColorPair(tw_top,tw_back);
  
  auto textwindow=std::make_shared<TextWindow>(wincolor,3,15,30,5);
  auto inputbox=std::make_shared<InputBox>(wincolor,8,10,3,20,4);
  auto bm=std::make_shared<SingleHandler>(20,3);
  auto aa=std::make_shared<MoveByInput>(5,8);
  auto test=std::make_shared<SingleHandler>(2,2);
  
  textwindow->ChangeText(L"Hey, what's your name?");
  inputbox->ChangeTitle(L"Enter your name.");
  bm->AttachDC(new BMimage("./assets/kinoko.bmp"));
  aa->AttachDC(new AAtext("./assets/human.aa"));
  test->AttachDC(new AAtext("./assets/test.aa"));
  
  gw.AttachEL(&gel);
  inputbox->AttachEL(&iel);
  inputbox->StartInput();
  gw.AddDCHandler(-10,test);
  gw.AddDCHandler(1,bm);
  gw.AddDCHandler(2,textwindow);
  gw.AddDCHandler(3,aa);
  gw.AddDCHandler(4,inputbox);
  while(!gel.IsEnd()){
    gw.Exec(im);
    gw.Draw();
    clock.WaitFrame();
  }
  return 0;
}

