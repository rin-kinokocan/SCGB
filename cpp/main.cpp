#include "scgb.hpp"
using namespace scgb;
using namespace scgb::Util;
int main(){
  GameWindow gw("ja_JP.UTF-8");
  GWEventListner gel;
  InputMap im;
  Clock clock;
  auto textwindow=std::make_shared<TextWindow>(COLOR_PAIR(4),5,1,20,5);
  auto textwindow2=std::make_shared<TextWindow>(L"Test",COLOR_PAIR(9),10,10,50,5);
  auto bm=std::make_shared<SingleHandler>(3,3);
  auto movable=std::make_shared<GOMovable>(10,10);
  auto test1=std::make_shared<SingleHandler>(5,5);
  textwindow->ChangeText(L"Hay, how are you doing?");
  bm->AttachDC(new BMimage("./assets/kinoko.bmp"));
  movable->AttachDC(new AAtext("./assets/test.aa"));
  test1->AttachDC(new AAtext("./assets/ebi.aa"));
 
  gw.AttachEL(&gel);
  gw.AddDCHandler(1,bm);
  gw.AddDCHandler(2,textwindow);
  gw.AddDCHandler(3,movable);
  gw.AddDCHandler(4,textwindow2);
  gw.AddDCHandler(5,test1);
  while(!gel.IsEnd()){
    gw.Exec(im);
    gw.Draw();
    clock.WaitFrame();
  }
  endwin();
  return 0;
}

