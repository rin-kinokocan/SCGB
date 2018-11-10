#pragma once
#include "define.h"
namespace scgb{
  class DrawingComponent{
  public:
    virtual void Draw(int x,int y){}
    DrawingComponent(){}
    virtual ~DrawingComponent(){}
  };
}

