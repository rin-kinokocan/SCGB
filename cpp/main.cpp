#include "scgb.hpp"
using namespace scgb;
using namespace scgb::Util;
int main(){
  GameWindow gw("ja_JP.UTF-8");
  GWEventListner gel;
  IBEventListner iel;
  InputMap im;
  Clock clock;
  auto textwindow=std::make_shared<TextWindow>(COLOR_PAIR(3),3,15,30,5);
  auto inputbox=std::make_shared<InputBox>(COLOR_PAIR(3),10,3,10,4);
  auto bm=std::make_shared<SingleHandler>(3,3);
  auto aa=std::make_shared<SingleHandler>(5,8);
  auto test=std::make_shared<SingleHandler>(2,2);

  textwindow->ChangeText(L"Hay, what's your name?");
  inputbox->ChangeTitle(L"Enter your name.");
  bm->AttachDC(new BMimage("./assets/kinoko.bmp"));
  aa->AttachDC(new AAtext("./assets/human.aa"));
  test->AttachDC(new AAtext("./assets/test.aa"));
  
  gw.AttachEL(&gel);
  inputbox->AttachEL(&iel);
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

