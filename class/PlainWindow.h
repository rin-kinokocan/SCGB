#pragma once
#include "BaseWindow.h"

namespace scgb{
  class PlainWindow:public BaseWindow{
    //just a rectangle of a given color.
  public:
    virtual void Draw();
    chtype ColorPair;
    PlainWindow(int,int,int,int,chtype);
  };
}
