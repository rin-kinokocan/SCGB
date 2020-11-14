#include "scgb.hpp"
#include "GameContext.hpp"
#include "TitleScene.hpp"
#include <iostream>
#include <map>
#include <unistd.h>
using namespace scgb;
using namespace std;

void Dev_CheckPalette(){
  move(0,0);
  for(int i=0;i<COLOR_PAIRS;i++){
    attron(COLOR_PAIR(i));
    addch('@');
    attroff(COLOR_PAIR(i));
  }
  refresh();
  sleep(10000);
}

int main(){
  bool isend=false;
  // All envioromental things
  CursesManager& cm=CursesManager::GetInstance();
  Color& col=Color::GetInstance();
  Clock clock(10);
  //GameContext
  GameContext gc;
  gc.ChangeScene(make_shared<TitleScene>(1,1));
  while(!isend){
    clear();
    wint_t input,tmp_in;
    int code,tmp_code;
    input=0;code=0;
    while(true){
      tmp_code=get_wch(&tmp_in);
      if(tmp_code==ERR)
    	break;
      else{
    	code=tmp_code;
    	input=tmp_in;
      }
    }
    switch(input){
    case KEY_RESIZE:
      cm.OnResize();
      break;
    default:
      break;
    }
    if(gc.IsEnd())
      break;
    gc.HandleInput(input,code);
    gc.Draw();
    refresh();    
    clock.WaitFrame();
  }
  return 0;
}
