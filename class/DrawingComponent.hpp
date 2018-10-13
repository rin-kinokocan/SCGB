#pragma once
#include "define.h"
namespace scgb{
  class DrawingComponent{
  protected:
    double x,y;
    int width,height;
    bool isHidden=false;
  public:
    virtual void Draw(){}
    virtual void Hide(){isHidden=true;}
    virtual void Show(){isHidden=false;}
    DrawingComponent(double px,double py,int w,int h){
      x=px;y=py;width=w;height=h;
}
    DrawingComponent(){}
    virtual ~DrawingComponent(){}
  };
}

