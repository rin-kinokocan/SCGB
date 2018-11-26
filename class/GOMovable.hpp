#pragma once
#include "SingleHandler.hpp"

namespace scgb{
  class GOMovable:public SingleHandler{
  public:
    virtual void Exec(InputMap im){
      if(im.GetBool(KEY_LEFT))
	this->x-=1;
      if(im.GetBool(KEY_RIGHT))
	this->x+=1;
      if(im.GetBool(KEY_UP))
	this->y-=1;
      if(im.GetBool(KEY_DOWN))
	this->y+=1;
    }
    GOMovable(double x,double y):SingleHandler(x,y){}
  };
}
