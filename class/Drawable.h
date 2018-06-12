#pragma once
#include "define.h"

namespace scgb{
  class Drawable{
    //interface for Drawing things.
    //follows Composite design pattern.
  protected:
    WindowContainer* parentcontainer=nullptr;
  public:
    virtual void Draw(){};
    virtual void Refresh(){};
    virtual void OnResize(){};
    virtual void DrawOnScreen(){};
    virtual cChar GetWholeScreen(int x,int y)=0;
    virtual void AddWholeScreen(int x,int y,cChar c)=0;
    virtual void Hide(){};
    virtual void Show(){};
    virtual ~Drawable(){};
    
    void SetParent(WindowContainer* a){parentcontainer=a;};
  };
}

