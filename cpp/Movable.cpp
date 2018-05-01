#include <unistd.h>
#include "../class/Movable.hh"
#include "../class/define.h"
using namespace scgb;

bool Movable::rmove(){
  this->x++;
  this->modify();
  this->windmove();
  return true;
}

bool Movable::lmove(){
  this->x--;
  this->modify();
  this->windmove();
  return true;
}

bool Movable::umove(){
  this->y--;
  this->modify();
  this->windmove();
  return true;
}

bool Movable::dmove(){
  this->y++;
  this->modify();
  this->windmove();
  return true;
}

bool Movable::modify(){
  int x,y,ax=this->width,ay=this->height;
  
  getmaxyx(stdscr,y,x);
  
  if(this->x + this->width > x)//too right
    ax=x-this->x;
  else if(this->x<0)//too left
    ax=this->width+this->x;
  
  if(this->y + this->height > y)//too down
    ay=y-this->y;
  else if(this->y<0)//too high
    ay=this->height+this->y;

  if(this->window==nullptr && ay>0 && ax>0){
    int tx=this->x,ty=this->y;
    if(this->x<0)
      tx=0;
    if(this->y<0)
      ty=0;
    this->window=newwin(ay,ax,ty,tx);
  }
  
  if(wresize(this->window,ay,ax)){
    delwin(this->window);
    this->window=nullptr;
    return false;
  }

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
