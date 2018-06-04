#pragma once
#include "Movable.hh"

namespace scgb{
  class PlainWindow:public Movable{
    //just a rectangle of a given color.
  public:
    virtual void Draw();
    bool isBox;
    chtype ColorPair;
    PlainWindow(int x,int y,int w,int h,chtype ColorPair=0,bool isBox=false);
  };
}
