#pragma once
#include "define.hpp"

namespace scgb{
  class Boundary{
  private:
    Vector2D origin;
    Vector2D size;
  public:
    Vector2D GetUpLeft(){
      return Vector2D(origin[0],origin[1]);
    }
    Vector2D GetBottomRight(){
      return Vector2D(origin[0]+size[0],origin[1]+size[1]);
    }
  };
}
