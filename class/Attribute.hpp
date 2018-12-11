#pragma once
#include "BWHandler.hpp"

namespace scgb{
  class Attribute:public LogicComponent{
    // Contains attributes for a Box.
  protected:
    attr_t attr;
  public:
    attr_t GetAttr(){return attr;}
    Attribute(attr_t a,int x,int y):BWHandler(w,y){attr=a;};
  }
}
