#pragma once
#include "ImageFile.hpp"

namespace scgb{
  class HandMadeImageFile:public ImageFile{
  public:
    void LoadImage(std::string filename){
      // Does nothing
    }
    HandMadeImageFile(int w,int h){
      width=w;
      height=h;
      pixels.resize(w*h);
      std::fill(pixels.begin(),pixels.end(),0);
    }
    HandMadeImageFile* Add(int x,int y,attr_t a){
      pixels[x+y*width]=a;
      return this;
    }
  };
}
