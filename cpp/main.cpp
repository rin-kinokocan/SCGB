#include <memory>
#include <csignal>
#include <cstdlib>
#include <unistd.h>
#include "../include/scgb.h"
#include "../class/Heli.hh"
using namespace scgb;

int main(){
  Screen::Init();
  auto test=new scgb::AAtext(10,10,"./assets/ebi.aa");
  pDrawable aa,bm1;
  aa.reset(test);
  bm1.reset(new scgb::BMimage(0,0,"./assets/kinoko.bmp"));
  Screen::AddDrawable(2,aa);
  Screen::AddDrawable(1,bm1);
  while(Screen::GetState()!=scgb::STA_DESTROY){
    //draw start
    Screen::Draw();
    Screen::Refresh();
    switch(Screen::GetEvent()){//event management
    case scgb::EVE_QUIT:
      Screen::Destroy();
      break;
    case scgb::EVE_PRINT:
      break;
    case scgb::EVE_RESIZE:
      Screen::Resize();
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
    usleep(10000);
  }
  return 0;
}

