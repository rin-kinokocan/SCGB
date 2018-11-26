#pragma once
#include "BaseWindow.hpp"

namespace scgb{
  class Block :public BaseWindow{
  protected:
    attr_t attr;
  public:
    Block(attr_t a,int w,int h):BaseWindow(w,h){attr=a;};
    virtual void Draw(int x,int y){
      InitDraw(x,y);
      for(int i=0;i<width*height;i++){
	AddChar(L' ',attr);
      }
    }
  };
}
