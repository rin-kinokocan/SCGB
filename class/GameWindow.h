#pragma once
#include "GameComponent.h"
#include "Drawable.h"

namespace scgb{
  class GameWindow:public GameObject{
  protected:
    Screen scr;
    InputManager im;
    InputMap map;
    std::map<int,std::shared_ptr<GameComponent>> gcs;
  public:
    void Draw(){
      scr.Draw();
      scr.Refresh();
    }
    void Exec(){
      im.Update();
      for(auto a:gcs){
	a.second->Exec();
      }
    }
    
    template <class T>
    WeakPtr<T> AddGameComponent(int l,GCBuilder* gcb){
      std::shared_ptr<GameComponent> b;
      auto db=gcb->GetDrawableBuilder();
      auto a=AddDrawable<Drawable>(l,db);
      gcb->SetIM(&map);
      gcb->SetDrawable(a);
      b.reset(gcb->GetResult());
      gcs.insert(std::pair<int,std::shared_ptr<GameComponent>>(l,b));
      return WeakPtr<T>(std::static_pointer_cast<T>(b));
    };
    template <class T>
    WeakPtr<T> AddDrawable(int l,DrawableBuilder* db){
      return scr.AddDrawable<T>(l,db);
    };
    GameWindow():map(im){
      auto id=im.CreateDevice<gainput::InputDeviceKeyboard>();
      map.MapBool(SCGB_LEFT,id,gainput::KeyLeft);
      map.MapBool(SCGB_RIGHT,id,gainput::KeyRight);
      map.MapBool(SCGB_UP,id,gainput::KeyUp);
      map.MapBool(SCGB_DOWN,id,gainput::KeyDown);
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
