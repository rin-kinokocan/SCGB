#include <cstdlib>
#include <unistd.h>
#include "../include/scgb.h"
using namespace scgb;

int main(){
  GameWindow gw;
  GWEventListner gel;
  gw.AttachEL(&gel);
  BMimageBuilder kinoko(20,10,"./assets/kinoko.bmp");
  AAtextBuilder ebi(20,0,"./assets/ebi.aa");
  IBBuilder ib(10,0,20,10,"Input Your Name");
  gw.AddDrawable<AAtext>(2,&ebi);
  gw.AddDrawable<BMimage>(3,&kinoko);
  while(!gel.IsEnd()){
    gw.Draw();
    usleep(2000);
  }
  endwin();
  return 0;
}

