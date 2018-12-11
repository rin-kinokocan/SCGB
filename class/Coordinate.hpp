#pragma once
#include "BaseModel.hpp"
#include "define.hpp"

namespace scgb{
  class Coordinate:public BaseModel<Vector2D>{
  protected:
    int x,y;
  public:
    Vector2D GetData(){
      return Vector2D(x,y);
    }
    Coordinate(int px,int py){
      x=px;y=py;
    }
    Coordinate():Coordinate(0,0){}
  };
}
