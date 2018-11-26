#pragma once
#include "define.hpp"
namespace scgb{
  class EventListner{
  public:
    virtual void notify(Event e,std::string str=NULL){};
  };
}
