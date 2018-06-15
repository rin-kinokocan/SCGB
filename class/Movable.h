#pragma once
#include "define.h"

namespace scgb{
  class Movable{
  //Interface for movable things.
  private:    
    virtual void rmove(){};
    virtual void lmove(){};
    virtual void umove(){};
    virtual void dmove(){};
  public:
    virtual void Move(Direction dir){
      switch(dir){
      case Left:
	lmove();
	break;
      case Right:
	rmove();
	break;
      case Up:
	umove();
	break;
      case Down:
	dmove();
	break;
      }
    };
    virtual ~Movable(){};
  };
}
