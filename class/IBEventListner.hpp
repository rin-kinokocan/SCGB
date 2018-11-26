#include "EventListner.hpp"

namespace scgb{
  class IBEventListner:public EventListner{
  private:
    bool isend=false;
  public:
    void notify(Event e,std::string str=NULL){
      if(e==EVE_ENDINPUT)
	isend=true;
    }
    bool IsEnd(){
      return isend;
    }
  };
}
