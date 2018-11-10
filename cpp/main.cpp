#include <unistd.h>
#include "scgb.h"
using namespace scgb;
using namespace scgb::Util;
int main(){
  GameWindow gw;
  GWEventListner gel;
  InputMap im;
  auto aa=std::make_shared<GameObject>(0,0);
  auto bm=std::make_shared<GameObject>(0,0);
  auto movable=std::make_shared<GOMovable>(10,10);
  
  aa->AttachDrawingComponent(new AAtext("./assets/cloud.aa"));
  bm->AttachDrawingComponent(new BMimage("./assets/kinoko.bmp"));
  movable->AttachDrawingComponent(new AAtext("./assets/ebi.aa"));
  gw.AttachEventListner(&gel);
  gw.AddGameObject(0,aa);
  gw.AddGameObject(1,bm);
  gw.AddGameObject(2,movable);
  while(!gel.IsEnd()){
    gw.Draw();
    gw.Exec(im);
    usleep(200);
  }
  endwin();
  return 0;
}

