#pragma once
#include "ImageFile.hpp"
#include "Color.hpp"
#include <fstream>

namespace scgb{
  class BitMapImageFile:public ImageFile{
  protected:
    void LoadImage(std::string filename){
      Color& color=Color::GetInstance();
      
      std::ifstream file(filename,std::ios::in | std::ios::binary);
      int data=0;
      if(file.is_open()==false){
	endwin();
	throw std::invalid_argument("cannot open file");
      }
      file.read((char*)&data,2);
      if(data!=19778){
	endwin();
	throw(std::runtime_error("Not a BitMap"+std::to_string(data)));
      }
      file.ignore(16);
      file.read((char*)&width,4);
      file.read((char*)&height,4);
      file.ignore(28);
      int w=width;
      int h=height;
      this->pixels.resize(w*h);
      for(int i=0;i<h;i++){
	for(int j=0;j<w;j++){
	 unsigned char r,g,b;
	 if(file.read((char*)&b,1) && file.read((char*)&g,1)&& file.read((char*)&r,1)){
	   int p=color.GetColorPair(r,g,b);
	   this->pixels[(h-i-1)*w+j]=COLOR_PAIR(p);
	 }
	}
	file.read((char*)&data,(w*3)%4);
      }
      file.close();
    }
  public:
    BitMapImageFile(std::string filename){
      LoadImage(filename);
    }
  };
}
