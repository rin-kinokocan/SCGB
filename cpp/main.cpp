#include <unistd.h>
#include "scgb.hpp"
using namespace scgb;
using namespace scgb::Util;
int main(){
  GameWindow gw;
  GWEventListner gel;
  InputMap im;
  auto aa=std::make_shared<GameObject>(0,0);
  auto bm=std::make_shared<GameObject>(0,0);
  auto movable=std::make_shared<GOMovable>(10,10);
  
  auto text=std::make_shared<TextWindow>(COLOR_PAIR(4),20,20);
  text->ChangeText(L"Hay, you can do this and more");
  aa->AttachDrawingComponent(text);
  bm->AttachDrawingComponent(new BMimage("./assets/kinoko.bmp"));
  movable->AttachDrawingComponent(new AAtext("./assets/ebi.aa"));
  
  gw.AttachEventListner(&gel);
  gw.AddGameObject(1,bm);
  gw.AddGameObject(3,movable);
  gw.AddGameObject(2,aa);
  while(!gel.IsEnd()){
    gw.Draw();
    gw.Exec(im);
    usleep(200);
  }
  endwin();
  return 0;
}

