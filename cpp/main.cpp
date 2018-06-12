#include <cstdlib>
#include <unistd.h>
#include "../include/scgb.h"
using namespace scgb;

int main(){
  Screen scr;
  scr.Init();
  scr.AddDrawable<BMimage>(1,new BMimage(20,0,"./assets/kinoko.bmp"));
  auto test=scr.AddDrawable<AAtext>(2,new AAtext(0,10,"./assets/ebi.aa"));
  auto input=scr.AddDrawable<InputBox>(3,new InputBox(10,0,20,10,17,"Input your name."));
  while(scr.GetState()!=State::STA_DESTROY){
    scr.Draw();
    scr.Refresh();
    auto a=scr.GetEvent();
    std::vector<wchar_t> data;
    switch(a){//event management
    case scgb::EVE_QUIT:
      scr.Destroy();
      break;
    case scgb::EVE_PRINT:
      data=input->GetInput();
      break;
    case scgb::EVE_RESIZE:
      scr.OnResize();
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
  }
  endwin();
  return 0;
}

