#include <unistd.h>
#include "scgb.h"
using namespace scgb;

int main(){
  Util::SetSigHandlers();
  GameWindow gw;
  GWEventListner gel;
  InputMap im;
  gw.AttachEventListner(&gel);
  gw.AddGameObject<GameObject<BMimage>>(1,new GameObject<BMimage>(new BMimage(-10,10,"./assets/kinoko.bmp")));
  auto hero=gw.AddGameObject<GOMovable<AAtext>>(2,new GOMovable<AAtext>(new AAtext(30,0,"./assets/ebi.aa")));
  while(!gel.IsEnd()){
    gw.Draw();
    gw.Exec(im);
    usleep(2000);
  }
  endwin();
  return 0;
}

