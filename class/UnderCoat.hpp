#pragma once
#include "DrawingComponent.hpp"

namespace scgb{
  class UnderCoat:public DrawingComponent{
  protected:
    std::vector<attr_t> colors;
  public:
    UnderCoat(int x=0,int y=0,int w=0,int h=0){
      colors.resize(w*h);
      SetTransparency(true);
    }
    DrawingComponent* Add(int x,int y,attr_t attr){
      colors[y*width+x]=attr;
      return this;
    }
    void Draw(){
      for(auto a:colors){
	AddChar(' ',a);
	auto cur=GetCursor();
	if(cur[0]>width){
	  MoveCursor(0,cur[1]+1);
	}
      }
    }
  };
}
