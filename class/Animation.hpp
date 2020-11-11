#pragma once
#include "DrawingComponent.hpp"
#include "AAfile.hpp"

namespace scgb{
  class Animation:public DrawingComponent{
  protected:
    int frame;
    int cur=0;
    AAfile aaf;
    bool DoRepeat=true;
  public:
    Animation(std::string filename,int f,int x=0,int y=0):DrawingComponent(x,y),frame(f),aaf(filename){
      auto s=aaf.GetSize();
      width=s[0];
      height=s[1]/f;
    }
    void Draw(){
      static int count=0;
      MoveCursor(0,-1*cur*height);
      AddStr(aaf.GetData(),0);
      count++;
      if(count>5){
	cur++;
	count=0;
      }
      if(cur>=frame && DoRepeat)
	cur=0;
    }
  };
}
