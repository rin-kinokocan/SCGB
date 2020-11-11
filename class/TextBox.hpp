#pragma once
#include "DrawingComponent.hpp"
#include <iostream>
namespace scgb{
  template<class T> class TextBox :public DrawingComponent{
    // Draw string inside of the box
    // T must be some kind of string.
  protected:
    T data;
  public:
    void Draw(){
      MoveCursor(0,0);
      for(auto d:data){	
	AddChar(d,0);
	auto cur=GetCursor();
	if(cur[0]>=width){
	  MoveCursor(0,cur[1]+1);
	}
      }
    }
    TextBox(T s,int x=0,int y=0,int w=10,int h=10):DrawingComponent(x,y,w,h),data(s){
      SetTransparency(true);
    }
  };
}
