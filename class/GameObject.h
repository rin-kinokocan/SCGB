#pragma once
#include "define.h"

namespace scgb{
  class EventListner{
  public:
    virtual void notify(Event e,std::string str=NULL){};
  };
  
  class GameObject{
    //base class for GUI components.
  protected:
    std::vector<EventListner*> els;
  public:
    virtual void Draw(){};
    virtual void AttachEL(EventListner* el){
      els.push_back(el);
    }
    virtual void SendMessage(Event e,std::string str=NULL){
      for(auto el:els){
	el->notify(e,str);
      }
    }
  };
  
}
