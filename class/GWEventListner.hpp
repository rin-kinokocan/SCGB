#pragma once
#include "EventListner.hpp"

namespace scgb{
  class GWEventListner:public EventListner{
  private:
    bool isend=false;
  public:
    void notify(Event e,std::string str=NULL){
      if(e==EVE_END)
	isend=true;
    }
    bool IsEnd(){
      return isend;
    }
  };
}
