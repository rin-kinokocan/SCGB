#pragma once
#include "DrawingComponent.hpp"
#include "Movable.h"

namespace scgb{
  class BaseWindow :public DrawingComponent, public Movable{
  private:
    int curx=0;
    int cury=0;
  protected:
    void InitDraw();
    bool MoveAfterDraw(int w);
    bool AddChar(cChar c);//for file reading things,I guess?
    bool DrawPolicy(int w);
 public:
    //Movable implementations
    virtual void rmove();
    virtual void lmove();
    virtual void umove();
    virtual void dmove();
    //Drawing methods
    void MoveCursor(int x,int y);
    void AddChar(cChar c,int x,int y);//for normal use.
    void AddStr(std::vector<cChar>,int x,int y);//to add string.
    
    BaseWindow(int,int,int,int);
    virtual ~BaseWindow(){}
  };
}
