#pragma once
#include <vector>
#include "EventListner.hpp"

namespace scgb{
  class ELHandler{
  protected:
    std::vector<EventListner*> els;
  public:
    virtual void AttachEL(EventListner* el){
      els.push_back(el);
    }
    virtual void SendMessage(Event e,std::string str=""){
      for(auto el:els){
	el->notify(e,str);
      }
    }
    virtual ~ELHandler(){}
  };
}

