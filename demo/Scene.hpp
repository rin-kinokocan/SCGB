#pragma once
#include "scgb.hpp"
#include "GameContext.hpp"

namespace scgb{
  class GameContext;
  class Scene:public CompositeDrawingComponent{
  public:
    virtual void HandleInput(GameContext& gc,wint_t input,int code)=0;
    Scene(int x=0,int y=0):CompositeDrawingComponent(x,y){}
  };
}
