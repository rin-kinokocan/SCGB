#include <unistd.h>
#include "scgb.hpp"
using namespace scgb;
using namespace scgb::Util;
int main(){
  GameWindow gw;
  GWEventListner gel;
  InputMap im;
  Clock clock;
  auto textwindow=std::make_shared<TextWindow>(COLOR_PAIR(4),5,0,20,5);
  auto bm=std::make_shared<SingleHandler>(0,0);
  auto movable=std::make_shared<GOMovable>(10,10);

  textwindow->ChangeText(L"Hay, how are you doing?");
  bm->AttachDC(new BMimage("./assets/kinoko.bmp"));
  movable->AttachDC(new AAtext("./assets/ebi.aa"));
  
  gw.AttachEL(&gel);
  gw.AddDCHandler(1,bm);
  gw.AddDCHandler(2,textwindow);
  gw.AddDCHandler(3,movable);
  while(!gel.IsEnd()){
    gw.Exec(im);
    gw.Draw();
    clock.WaitFrame();
  }
  endwin();
  return 0;
}

