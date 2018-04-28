#include "../class/Color.hh"
#include "../class/BMimage.h"
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
  wmove(this->window,0,0);
  werase(this->window);
  for(int i:this->Pixels){
    wattron(this->window,COLOR_PAIR(i));
    waddwstr(this->window,L"  ");
    wattroff(this->window,COLOR_PAIR(i));
  }
}

void BMimage::Refresh(){
  touchwin(this->window);
  wnoutrefresh(this->window);
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
  this->width=this->bi.biWidth*2;
  this->height=this->bi.biHeight;
  this->window=newwin(this->height,this->width,y,x);
  this->file.seekg(this->bf.bfOffBits);
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

