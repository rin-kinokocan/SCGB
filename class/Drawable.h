#pragma once
#include "define.h"
#include "Mediator.h"

namespace scgb{
  class Drawable{
    //interface for Drawing things.
    //follows Composite design pattern.
  protected:
    EventMediator* parentmediator=nullptr;
  public:
    virtual void Draw(){};
    virtual void Refresh(){};
    virtual void Resize(){};
    virtual void DrawOnScreen(){};
    virtual void Hide(){};
    virtual void Show(){};
    virtual ~Drawable(){};
    
    void SetMediator(EventMediator* a){parentmediator=a;};
    virtual void EventHandler(int i){parentmediator->SendEvent(i);};
  };
}

