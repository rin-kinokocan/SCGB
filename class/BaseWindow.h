#pragma once
#include "../include/define.h"
#include "Drawable.h"
#include <memory>
#include <map>

namespace scgb{
  class BaseWindow :public Drawable{
  protected:
    int width;
    int height;
    int x;
    int y;
  public:
    WinPtr window;
    void Resize(){
      mvwin(this->window,this->y,this->x);
      wresize(this->window,this->height,this->width);
    };
    const bool DrawLimit(){
      int a,b;
      getyx(this->window,a,b);
      if(a==this->width-1){
	return true;
      }
      return false;
    };

    virtual ~BaseWindow(){};
  };
}
