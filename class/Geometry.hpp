#pragma once
#include "BaseModel.hpp"
#include "define.hpp"

namespace scgb{
  class Geometry:public BaseModel<Vector2D>{
  protected:
    int width,height;
  public:
    Vector2D GetData(){
      return Vector2D(width,height);
    }
    Geometry(int w,int h){
      width=w;height=h;
    }
    Geometry(Vector2D geo){
      width=geo[0];height=geo[1];
    }
    Geometry():Geometry(0,0){}
  };
  typedef Geometry Coordinate;
  typedef Geometry Boundary;
}
