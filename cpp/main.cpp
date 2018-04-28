#include <memory>
#include <csignal>
#include <cstdlib>
#include <unistd.h>
#include "../include/scgb.h"
#include "../class/Heli.hh"

int main(){
  scgb::Screen scr(0,0);
  scgb::pDrawable aa,bm1,bm2;
  aa.reset(new scgb::AAtext(10,10,"./assets/ebi.aa"));
  bm1.reset(new scgb::BMimage(0,0,"./assets/kinoko.bmp"));
  scr.AddDrawable(1,aa);
  scr.AddDrawable(2,bm1);
  auto test=scr.GetDrawable(1);
  while(scr.GetState()!=scgb::STA_DESTROY){
    switch(scr.GetEvent()){//event management
    case scgb::EVE_QUIT:
      scr.Destroy();
      break;
      
    case scgb::EVE_PRINT:
      break;
      
    case scgb::EVE_RESIZE:
      scr.Resize();
      break;

    case scgb::EVE_RIGHT:
      test->Move(scgb::Right);
      break;
    case scgb::EVE_LEFT:
      test->Move(scgb::Left);
      break;
    case scgb::EVE_UP:
      test->Move(scgb::Up);
      break;
    case scgb::EVE_DOWN:
      test->Move(scgb::Down);
      break;
    default:
      break;
    }
    //draw start
    usleep(10000);
    scr.Draw();
    scr.Refresh();
  }
  return 0;
}

