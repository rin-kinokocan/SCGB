#pragma once
#include "define.h"
#include "Movable.h"

namespace scgb{
  class Drawable:public Movable{
    //interface for Drawing things.
    //follows Composite design pattern.
  protected:
    WindowContainer* parentcontainer=nullptr;
    virtual cChar GetWholeScreen(int x,int y)=0;
    virtual void AddWholeScreen(int x,int y,cChar c)=0;
  public:
    virtual void SetParent(WindowContainer* a){parentcontainer=a;};
    virtual void Draw(){};
    virtual void Refresh(){};
    virtual void OnResize(){};
    virtual void DrawOnScreen(){};
    virtual void Hide(){};
    virtual void Show(){};
    virtual ~Drawable(){};

    friend WindowContainer;
  };
}

