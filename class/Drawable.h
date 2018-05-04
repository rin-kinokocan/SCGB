#pragma once
#include <string>
#include <vector>
#include "Screen.h"

namespace scgb{
  class Drawable{
    //interface for Drawing things.
  public:
    virtual void Draw()=0;
    virtual void DrawOnScreen()=0;
    virtual void Refresh()=0;
    virtual void Resize()=0;
    virtual ~Drawable(){};
  };
  typedef std::wstring DrawString;
}

