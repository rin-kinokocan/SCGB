#include "scgb.hpp"
#include "GameContext.hpp"
#include "TitleScene.hpp"
#include <iostream>
#include <map>
using namespace scgb;
using namespace std;

int main(){
  bool isend=false;
  // All envioromental things
  CursesManager& cm=CursesManager::GetInstance();
  Color& col=Color::GetInstance();
  Clock clock(10);
  Input input;
  
  //GameContext
  GameContext gc;
  gc.ChangeScene(make_shared<TitleScene>(1,1));
  while(!isend){
    erase();
    auto data=input.GetInput();
    switch(data[1]){
    case KEY_RESIZE:
      cm.OnResize();
      break;
    default:
      break;
    }
    if(gc.IsEnd())
      break;
    gc.HandleInput(data[0],data[1]);
    gc.Update();
    gc.Draw();
    refresh();    
    clock.WaitFrame();
  }
  return 0;
}
