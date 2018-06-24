#pragma once
#include "GameComponent.h"
#include "Drawable.h"

namespace scgb{
  class GameWindow:public GameObject{
  protected:
    Screen scr;
    std::map<int,std::shared_ptr<GameComponent>> gcs;
  public:
    void Draw(){
      scr.Draw();
      scr.Refresh();
    }
    
    template <class T>
    WeakPtr<T> AddGameComponent(int l,GCBuilder* gcb){
      	std::shared_ptr<GameComponent> b;
	b.reset(gcb->GetResult());
	gcs.insert(std::pair<int,std::shared_ptr<GameComponent>>(l,b));
	return WeakPtr<T>(std::static_pointer_cast<T>(b));
    };
    template <class T>
    WeakPtr<T> AddDrawable(int l,DrawableBuilder* db){
      return scr.AddDrawable<T>(l,db);
    };
    GameWindow(){
    }
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
