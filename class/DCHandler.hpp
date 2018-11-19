#pragma once
#include "LogicComponent.hpp"

namespace scgb{
  class DCHandler:public LogicComponent{
  protected:
    bool isHidden=false;
    double x,y;//upleft coodinates
  public:
    virtual void Draw()=0;
    virtual void Hide(){isHidden=true;}
    virtual void Show(){isHidden=false;}
    DCHandler(double x,double y){
      this->x=x;this->y=y;
    }
    virtual ~DCHandler(){}
  };
}
