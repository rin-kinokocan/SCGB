#include "class/Color.hh"
#include "class/BMimage.h"
#include <unistd.h>

using namespace scgb;

void BMimage::ReadFile(){
 
  this->file.read(reinterpret_cast<char*>(&(this->bf.bfType)),2);
  if(bf.bfType!=19778){//"BM" in hex,but I'm not sure how to write hex.
    printf("%d\n",bf.bfType);
    throw 1;
  }
  this->file.read(reinterpret_cast<char*>(&(this->bf.bfSize)),4);
  this->file.read(reinterpret_cast<char*>(&(this->bf.bfReserved1)),2);
  this->file.read(reinterpret_cast<char*>(&(this->bf.bfReserved2)),2);
  this->file.read(reinterpret_cast<char*>(&(this->bf.bfOffBits)),4);

  this->file.read(reinterpret_cast<char*>(&(this->bi.biSize)),4);
  this->file.read(reinterpret_cast<char*>(&(this->bi.biWidth)),4);
  this->file.read(reinterpret_cast<char*>(&(this->bi.biHeight)),4);
  this->file.read(reinterpret_cast<char*>(&(this->bi.biPlanes)),2);
  this->file.read(reinterpret_cast<char*>(&(this->bi.biBitCount)),2);
  this->file.read(reinterpret_cast<char*>(&(this->bi.biCompression)),4);
  this->file.read(reinterpret_cast<char*>(&(this->bi.biSizeImage)),4);
  this->file.read(reinterpret_cast<char*>(&(this->bi.biXPixPerMeter)),4);
  this->file.read(reinterpret_cast<char*>(&(this->bi.biYPixPerMeter)),4);
  this->file.read(reinterpret_cast<char*>(&(this->bi.biClrUsed)),4);
  this->file.read(reinterpret_cast<char*>(&(this->bi.biClrImporant)),4);
}

void BMimage::Draw(){
  InitDraw();
  for(int i:this->Pixels){
    cchar_t a;
    a.chars[0]=L' ';a.chars[1]=L'\0';
    a.attr=COLOR_PAIR(i)|A_PROTECT;
    AddChar(a);
    AddChar(a);
  }
}

BMimage::BMimage(int x,int y,const char* filename)
  :file(filename,std::ios::in | std::ios::binary)
{
  this->x=x;
  this->y=y;
  if(file.is_open()==false){
    throw std::invalid_argument("cannot open file");
  }
  this->ReadFile();
  this->width=this->bi.biWidth*2+1;//+1 is for return.
  this->height=this->bi.biHeight;
  FitToScreen();
  int w=this->bi.biWidth;
  int h=this->bi.biHeight;
  this->Pixels.resize(w*h);
  for(int i=0;i<h;i++){
    for(int j=0;j<w;j++){
      unsigned char r,g,b;
      if(this->file.read(reinterpret_cast<char*>(&b),1)&&
	 this->file.read(reinterpret_cast<char*>(&g),1)&&
	 this->file.read(reinterpret_cast<char*>(&r),1)){
	int p=Color::GetWebSafeColor(r,g,b);
	int x=j,y=h-1-i;
	int pos=y*w+x;
	this->Pixels[pos]=p;
      }
    }
  }
  this->file.close();
}

BMimage::~BMimage(){
  sleep(1);
  delwin(this->window);
}

