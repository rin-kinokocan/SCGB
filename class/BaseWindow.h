#pragma once
#include "define.h"
#include "Drawable.h"
#include <vector>
#include <memory>
#include <map>

namespace scgb{
  class BaseWindow :public Drawable{
  protected:
    int width;
    int height;
    int x;
    int y;
    WinPtr window;
  public:
    void Resize(){
      mvwin(this->window,this->y,this->x);
      wresize(this->window,this->height,this->width);
    };
    std::vector<int> GetGlobalCursorPos(){
      int posx,posy;getbegyx(this->window,posy,posx);
      int cx,cy;getyx(this->window,cy,cx);
      posx+=cx;posy+=cy;
      vector<int> a;a.resize(2);
      a[0]=posx;a[1]=posy;
      return a;
    };
    virtual ~BaseWindow(){};
  };
}
