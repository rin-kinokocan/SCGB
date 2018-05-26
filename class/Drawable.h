#pragma once
#include <string>
#include <vector>

namespace scgb{
  class Drawable{
    //interface for Drawing things.
  public:
    virtual void Draw(){};
    virtual void Refresh(){};
    virtual void Resize(){};
    virtual void DrawOnScreen(){};
    virtual ~Drawable(){};
  };
}

