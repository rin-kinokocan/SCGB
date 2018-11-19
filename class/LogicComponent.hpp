#pragma once
#include "define.hpp"
#include "InputMap.hpp"
#include "EventListner.hpp"

namespace scgb{
  class LogicComponent{
    //Do something logical. But contains drawing function.
  public:
    virtual void Exec(InputMap im){};
    virtual ~LogicComponent(){};
  };

}
