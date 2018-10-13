#include "GameObject.hpp"

namespace scgb{
  template <class T>
  class GOMovable:public GameObject<T>{
  public:
    virtual void Exec(InputMap im){
      if(im.GetBool(SCGB_LEFT))
	this->dcp->Move(Left);
      if(im.GetBool(SCGB_RIGHT))
	this->dcp->Move(Right);
      if(im.GetBool(SCGB_UP))
	this->dcp->Move(Up);
      if(im.GetBool(SCGB_DOWN))
	this->dcp->Move(Down);
    }
    GOMovable(T* pwpd)
      :GameObject<T>(pwpd){}
  };
}
