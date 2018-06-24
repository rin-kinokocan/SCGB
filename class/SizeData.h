#pragma once
#include "define.h"

namespace scgb{
  class SizeData{
    //class to enable Drawables to communicate with
    //it's container.
  private:
    double x,y,width,height;
  public:
    SizeData(){}
    SizeData(int x,int y,int w,int h){
      this->x=x;
      this->y=y;
      width=w;height=h;
    }
    virtual Vector2D GetMaxXY(){
      Vector2D v;
      v.resize(2);
      v[0]=x+width;
      v[1]=y+height;
      return v;
    };
    virtual  Vector2D GetMinXY(){
      Vector2D v;
      v.resize(2);
      v[0]=x;
      v[1]=y;
      return v;
    };
    friend WindowContainer;
  };
  
}

