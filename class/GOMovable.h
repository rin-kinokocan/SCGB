#include "GameObject.hpp"

namespace scgb{
  class GOMovable:public GameObject{
  public:
    virtual void Exec(InputMap im){
      if(im.GetBool(SCGB_LEFT))
	this->x--;
      if(im.GetBool(SCGB_RIGHT))
	this->x++;
      if(im.GetBool(SCGB_UP))
	this->y--;
      if(im.GetBool(SCGB_DOWN))
	this->y++;
    }
    GOMovable(double x,double y):GameObject(x,y){}
  };
}
