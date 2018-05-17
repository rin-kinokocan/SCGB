#pragma once
#include "define.h"
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
    Movable(){};
    Movable(int,int,int,int);
    virtual ~Movable(){};
  };
}
