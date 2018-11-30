#pragma once
#include "define.hpp"
namespace scgb{
  class DrawingComponent{
  public:
    virtual void Draw(int x,int y){}
    virtual ~DrawingComponent(){}
  };
}

