#include <unistd.h>
#include "scgb.hpp"
using namespace scgb;
using namespace scgb::Util;
int main(){
  GameWindow gw;
  GWEventListner gel;
  InputMap im;
  auto textwindow=std::make_shared<TextWindow>(COLOR_PAIR(4),5,0,20,5);
  auto bm=std::make_shared<GameObject>(0,0);
  auto movable=std::make_shared<GOMovable>(10,10);

  textwindow->ChangeText(L"Hay, how are you doing?");
  bm->AttachDrawingComponent(new BMimage("./assets/kinoko.bmp"));
  movable->AttachDrawingComponent(new AAtext("./assets/ebi.aa"));
  
  gw.AttachEventListner(&gel);
  gw.AddGameObject(1,bm);
  gw.AddGameObject(2,textwindow);
  gw.AddGameObject(3,movable);
  while(!gel.IsEnd()){
    gw.Draw();
    gw.Exec(im);
    usleep(200);
  }
  endwin();
  return 0;
}

