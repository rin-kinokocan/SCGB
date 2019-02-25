#pragma once
#include "BaseModel.hpp"

namespace scgb{
  class Attribute:public BaseModel<attr_t>{
    // Contains attributes
  protected:
    attr_t attr;
  public:
    attr_t GetData(){return attr;}
    Attribute(attr_t a){attr=a;}
  };
}
