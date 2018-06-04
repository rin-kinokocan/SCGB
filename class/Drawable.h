#pragma once

namespace scgb{
  class Drawable{
    //interface for Drawing things.
  public:
    virtual void Draw(){};
    virtual void Refresh(){};
    virtual void Resize(){};
    virtual void DrawOnScreen(){};
    virtual void Hide(){};
    virtual void Show(){};
    virtual ~Drawable(){};
  };
}

