#include <unistd.h>
#include "../class/Movable.hh"
#include "../class/define.h"
using namespace scgb;

bool Movable::rmove(){
  this->x++;
  FitToScreen();
  this->windmove();
  return true;
}

bool Movable::lmove(){
  this->x--;
  FitToScreen();
  this->windmove();
  return true;
}

bool Movable::umove(){
  this->y--;
  FitToScreen();
  this->windmove();
  return true;
}

bool Movable::dmove(){
  this->y++;
  FitToScreen();
  this->windmove();
  return true;
}

bool Movable::Move(Direction dir){
  switch(dir) {
  case Right:
    this->rmove();
    break;
  case Left:
    this->lmove();
    break;
  case Up:
    this->umove();
    break;
  case Down:
    this->dmove();
    break;
  }
  return true;
}

bool Movable::windmove(){
  int tx=this->x,ty=this->y;
  if(this->x<0)
    tx=0;
  if(this->y<0)
    ty=0;
  mvwin(this->window,ty,tx);
  return true;
}

Movable::Movable(int x,int y,int w,int h)
  :BaseWindow(x,y,w,h){
}
