#include "Color.hpp"
#include "BMimage.hpp"
#include "define.hpp"

using namespace scgb;

void BMimage::Draw(int x,int y){
  InitDraw(x,y);
  for(int i:this->pixels){
    AddStr(L"  ",COLOR_PAIR(i));
  }
}

BMimage::BMimage(std::string filename):BaseWindow(0,0){
  std::ifstream file(filename,std::ios::in | std::ios::binary);
  int data;
  if(file.is_open()==false){
    throw std::invalid_argument("cannot open file");
  }
  file.read((char*)&data,2);
  if(data!=19778)
    throw(std::runtime_error("Not a BitMap"));
  file.ignore(16);
  file.read((char*)&width,4);
  file.read((char*)&height,4);
  file.ignore(28);
  int w=width;
  int h=height;
  width*=2;
  this->pixels.resize(w*h);
  for(int i=0;i<h;i++){
    for(int j=0;j<w;j++){
      unsigned char r,g,b;
      if(file.read(reinterpret_cast<char*>(&b),1)&&
	 file.read(reinterpret_cast<char*>(&g),1)&&
	 file.read(reinterpret_cast<char*>(&r),1)){
	int p=Color::GetColor(r,g,b);
	int x=j,y=h-1-i;
	int pos=y*w+x;
	this->pixels[pos]=p;
      }
    }
  }
  file.close();
}

