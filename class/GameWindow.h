#pragma once
#include "LogicComponent.hpp"

namespace scgb{
  class GameObject;
  class GameWindow:public LogicComponent{
  protected:
    std::map<int,std::shared_ptr<LogicComponent>> lcs;
  public:
    void Draw(){
      erase();
      for(auto lc:lcs){
	lc.second->Draw();
      }
      refresh();
    }
    
    void Exec(InputMap im){
      im.Update();
      if(im.GetBool(SCGB_RESIZE)){
	Screen scr;
	scr.OnResize();
      }
      for(auto a:lcs){
	a.second->Exec(im);
      }
      if(im.GetBool(SCGB_QUIT)){
	SendMessage(EVE_END);
      }
    }

    void AddGameObject(int l,std::shared_ptr<GameObject> lc){
      lcs[l]=lc;
    }
    
    GameWindow(){
      Screen scr;
      scr.Init();
    }
    
    ~GameWindow(){}
  };
  
  class GWEventListner:public EventListner{
  private:
    bool isend=false;
  public:
    void notify(Event e,std::string str=NULL){
      if(e==EVE_END)
	isend=true;
    }
    bool IsEnd(){
      return isend;
    }
  };
}
