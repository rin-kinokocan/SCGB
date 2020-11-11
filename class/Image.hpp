#pragma once
#include "DrawingComponent.hpp"
#include "BitMapImageFile.hpp"
#include <memory>

namespace scgb{
  class Image :public DrawingComponent{
  protected:
    std::shared_ptr<ImageFile> img;
  public:
     Image(ImageFile& img,int x=0,int y=0):DrawingComponent(x,y){
      this->img=std::shared_ptr<ImageFile>(&img);
      auto size=this->img->GetSize();
      width=size[0];
      height=size[1];
    }
    Image(std::shared_ptr<ImageFile> img,int x=0,int y=0):DrawingComponent(x,y){
      this->img=img;
      auto size=this->img->GetSize();
      width=size[0];
      height=size[1];
    }

    Image(std::string f,int x=0,int y=0):DrawingComponent(x,y){
      this->img=std::make_shared<BitMapImageFile>(std::move(BitMapImageFile(f)));
      auto size=this->img->GetSize();
      width=size[0];
      height=size[1];
    }
    void Draw(){
      MoveCursor(0,0);
      const std::vector<attr_t>& pixels=img->GetData();
      for(int i=0;i<height;i++){
	for(int j=0;j<width;j++){
	  AddStr(" ",pixels[i*width+j]);
	}
	auto cur=GetCursor();
	MoveCursor(0,cur[1]+1);
      }
    }
  };
}

