#pragma once
#include "define.hpp"
#include "WindowInfo.hpp"

class BaseView;
template <class T> class BaseModel;
namespace scgb{
  class BaseController{
  public:
    virtual void Draw()=0;
    explicit BaseController(Geometry* geo,Coordinate* coord):wi(geo,coord){
    }
    
  protected:
    WindowInfo wi;
  };
}
