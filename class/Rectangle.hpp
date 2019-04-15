#pragma once
#include "DrawingComponent.hpp"

namespace scgb{
  class Rectangle:public DrawingComponent{
  protected:
    Vector2D size;
    attr_t attr=0;
  public:
    void Draw(){
      InitDraw();
      for(int i=0;i<size[1];i++){
	for(int j=0;j<size[0];j++){
	  AddChar(L' ',attr);
	}
	ChangeLine();
      }
    }
    void SetSize(int x,int y){
      size[0]=x;
      size[1]=y;
    }
    void SetAttr(attr_t a){
      attr=a;
    }
  };
}
