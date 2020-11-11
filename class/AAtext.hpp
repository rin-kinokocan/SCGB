#pragma once
#include "DrawingComponent.hpp"
#include "AAfile.hpp"

namespace scgb{
  class AABox :public DrawingComponent{
    // Draws things in datafile (with Unicode chars).
  public:
    void Draw(){
      MoveCursor(0,0);
      AddStr(datafile.GetData(),0);
    }
    TextBox(DataFile& f,int x=0,int y=0,int w=0,int h=0):DrawingComponent(x,y,w,h),datafile(f){
     }
  protected:
    DataFile& datafile;
  };
}
