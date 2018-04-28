#pragma once
#include "BaseWindow.h"

namespace scgb{
  
  enum Direction{
    Right,
    Left,
    Up,
    Down,
  };

  class Movable :public BaseWindow{
  private:    
    bool rmove();
    bool lmove();
    bool umove();
    bool dmove();
    bool modify();
    bool windmove();
  public:
    bool Move(Direction dir);
    virtual ~Movable(){};
  };
  typedef int Layer;
  typedef std::shared_ptr<scgb::Movable> pDrawable;
  typedef std::map<Layer,scgb::pDrawable> DrawList;
}
