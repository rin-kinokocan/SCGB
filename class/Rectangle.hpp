#pragma once
#include "DrawingComponent.hpp"

namespace scgb{
  class Rectangle:public DrawingComponent{
  protected:
    attr_t attr=0;
  public:
    Rectangle(attr_t a,int x=0,int y=0,int w=0,int h=0):DrawingComponent(x,y,w,h),attr(a){}
    void Draw(){
      MoveCursor(0,0);
      for(int i=0;i<height;i++){
	for(int j=0;j<width;j++){
	  if(i==0){
	    if(j==0){
	      AddChar(L'┌',attr);
	    }
	    else if(j==width-1){
	      AddChar(L'┐',attr);
	    }
	    else{
	      AddChar(L'─',attr);
	    }
	  }
	  else if(i==height-1){
	    if(j==0){
	      AddChar(L'└',attr);
	    }
	    else if(j==width-1){
	      AddChar(L'┘',attr);
	    }
	    else{
	      AddChar(L'─',attr);
	    }
	  }
	  else if(j==0 || j==width-1){
	    AddChar(L'│',attr);
	  }
	  else{
	    AddChar(L' ',attr);
	  }
	}
	auto cur=GetCursor();
	MoveCursor(0,cur[1]+1);
      }
    }
  };
}
