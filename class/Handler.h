#pragma once

namespace scgb{
  class EventMediator;
  class Handler{
  protected:
    virtual void EventHandler(int i){};
    friend EventMediator;
  };}
