#pragma once
#include <memory>

namespace scgb{
  class Geometry;
  class Coordinate;
  
  class BaseView{
    // Draws something on screen.
  public:
    virtual void Draw()=0;
  protected:
    std::shared_ptr<Geometry> boundary;
    std::shared_ptr<Coordinate> coordinate;
  };
}
