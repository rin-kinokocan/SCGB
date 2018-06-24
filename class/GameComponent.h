#pragma once
#include "GameObject.h"

namespace scgb{
  class GameComponent{
  protected:
    int x,y,width,height;
  public:
    GameComponent(int,int,int,int);
  };
  
  class GCBuilder{
  public:
    virtual GameComponent* GetResult()=0;
  };
}
