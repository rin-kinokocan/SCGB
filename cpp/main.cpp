#include <unistd.h>
#include "../include/scgb.h"
using namespace scgb;

int main(){
  GameWindow gw;
  GWEventListner gel;
  gw.AttachEL(&gel);
  BMimageBuilder bmi(20,10,"./assets/kinoko.bmp");
  AAtextBuilder aa(20,0,"./assets/ebi.aa");
  GCMovableBuilder ebi(&aa);
  gw.AddDrawable<BMimage>(1,&bmi);
  auto hero=gw.AddGameComponent<GCMovable>(2,&ebi);
  while(!gel.IsEnd()){
    gw.Draw();
    gw.Exec();
    usleep(2000);
  }
  endwin();
  return 0;
}

