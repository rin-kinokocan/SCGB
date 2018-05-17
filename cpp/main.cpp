#include <cstdlib>
#include <unistd.h>
#include "../include/scgb.h"
using namespace scgb;

int main(){
  Screen::Init();
  Screen::AddDrawable<BMimage>(1,new BMimage(-5,0,"./assets/kinoko.bmp"));
  auto test=Screen::AddDrawable<AAtext>(2,new AAtext(0,10,"./assets/ebi.aa"));
  Screen::AddDrawable<UserInput>(3,new UserInput(10,0,20,10));
  
  while(Screen::GetState()!=scgb::STA_DESTROY){
    auto a=Screen::GetEvent();
    switch(a){//event management
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
    //draw start
    Screen::Draw();
    Screen::Refresh();
    usleep(10000);
  }
  endwin();
  return 0;
}

