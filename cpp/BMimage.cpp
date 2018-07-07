#include "Color.hh"
#include "BMimage.h"
#include "define.h"

using namespace scgb;

void BMimage::Draw(){
  InitDraw();
  for(int i:this->Pixels){
    auto a=Util::make_cChar(' ',COLOR_PAIR(i)|A_PROTECT);
    AddChar(a);
    AddChar(a);
  }
}

BMimage::BMimage(int x,int y,SizeData* psd,std::string filename)
  :BaseWindow(x,y,0,0,psd)
{
  File file(filename,std::ios::in | std::ios::binary);
  int data;
  this->x=x;
  this->y=y;
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

  this->Pixels.resize(w*h);
  for(int i=0;i<h;i++){
    for(int j=0;j<w;j++){
      unsigned char r,g,b;
      if(file.read(reinterpret_cast<char*>(&b),1)&&
	 file.read(reinterpret_cast<char*>(&g),1)&&
	 file.read(reinterpret_cast<char*>(&r),1)){
	int p=Color::GetColor(r,g,b);
	int x=j,y=h-1-i;
	int pos=y*w+x;
	this->Pixels[pos]=p;
      }
    }
  }
  file.close();
}

