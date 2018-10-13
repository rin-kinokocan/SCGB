#pragma once
#include "LogicComponent.hpp"

namespace scgb{
  class GameWindow:public LogicComponent{
  protected:
    std::map<int,std::shared_ptr<LogicComponent>> lcs;
    Screen scr;
    
  public:
    void Draw(){
      clear();
      for(auto lc:lcs){
	lc.second->Draw();
      }
      scr.Refresh();
    }
    
    void Exec(InputMap im){
      im.Update();
      if(im.GetBool(SCGB_RESIZE))
	scr.OnResize();
      
      for(auto a:lcs){
	a.second->Exec(im);
      }
      if(im.GetBool(SCGB_QUIT)){
	SendMessage(EVE_END);
      }
    }

    template <class T>
    WeakPtr<T> AddGameObject(int l,T* lc){
      //I know it's a bad idea. I know it.
      std::shared_ptr<LogicComponent> s(lc);
      lcs[l]=s;
      return WeakPtr<T>(std::static_pointer_cast<T>(s));
    }
    
    GameWindow(){
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
