#pragma once
#include "SingleHandler.hpp"

namespace scgb{
  class GOMovable:public SingleHandler{
  public:
    virtual void Exec(InputMap im){
      if(im.GetBool(SCGB_LEFT))
	this->x-=1;
      if(im.GetBool(SCGB_RIGHT))
	this->x+=1;
      if(im.GetBool(SCGB_UP))
	this->y-=1;
      if(im.GetBool(SCGB_DOWN))
	this->y+=1;
    }
    GOMovable(double x,double y):SingleHandler(x,y){}
  };
}
