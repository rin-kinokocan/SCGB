#pragma once
#include "Handler.h"

namespace scgb{
  class EventMediator{
  protected:
    Handler* pointer;
  public:
    EventMediator(Handler* a){
      pointer=a;
    }
    void SendEvent(int i){
      pointer->EventHandler(i);
    }
  };
}
