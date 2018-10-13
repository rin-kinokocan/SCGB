#pragma once
#include "define.h"
#include "InputMap.h"
#include "EventListner.hpp"

namespace scgb{
  class LogicComponent{
    //Do something logical. But contains drawing function.
  protected:
    std::vector<EventListner*> els;
  public:
    virtual void Draw(){};
    virtual void Exec(InputMap im){};
    virtual void AttachEventListner(EventListner* el){
      els.push_back(el);
    }
    virtual void SendMessage(Event e,std::string str=""){
      for(auto el:els){
	el->notify(e,str);
      }
    }
    virtual ~LogicComponent(){};
  };

}
