#pragma once
#include "define.h"

namespace scgb{
  class SizeData{
    //class to enable Drawables to communicate with
    //it's container.
  private:
    double x,y,width,height;
  public:
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
  
  class MaxSizeData:public SizeData{
    //size data for screen.
    //always shows (0,0) to (COLS,RAWS).
  public:
    Vector2D GetMaxXY(){
      Vector2D v;
      v.resize(2);
      getmaxyx(stdscr,v[1],v[0]);
      return v;
    };
    Vector2D GetMinXY(){
      Vector2D v;
      v.resize(2);
      v[0]=0;
      v[1]=0;
      return v;
    };
  };
}

