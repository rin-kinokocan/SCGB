#include "class/AAtext.h"
#include <locale>
#include <unistd.h>
#include <unicode/utypes.h>
#include <string>

using namespace scgb;

void AAtext::Draw(){
  InitDraw();
  Vector2D cur;
  Vector2D max;
  int d;
  for(auto c:data){
    cur=GetXY();
    max=GetMaxXY();
    d=max[0]-cur[0]-1;
    int w=wcwidth(c);
    auto v=GetVirtualCursorPos();
    switch(c){
    case L' ':
    case L'　':
      DrawTransparent(w);
      break;
    case L'\n':
      if(v[1]>=0){
	for(int i=0;i<d;i++)
	  DrawTransparent(1,true);
      }
    default:
      cchar_t a;
      a.chars[0]=c;
      a.chars[1]=L'\0';
      a.attr=0;
      AddChar(a);
      break;
    }
  }
  for(int i=0;i<d;i++)
    DrawTransparent(1,true);
  OnReturn();
}

AAtext::AAtext(int x,int y,std::string filename)
{
  WFile file(filename,std::ios::binary);
  file.imbue(std::locale("ja_JP.UTF-8"));  
  if(file.is_open()!=false){
    int w=1,h=1,mw=0;
    file.clear();
    file.seekg(0,std::ios::beg);
    for(wchar_t c;file.get(c);){
      switch(c){
      case L'\n':
	h++;
	w=0;
	break;
      default:
	w+=wcwidth(c);
	if(w>mw)
	  mw=w;
	break;
      }
      data.push_back(c);
    }
    file.close();
    mw+=1;//includes space for return.
    this->x=x;
    this->y=y;
    this->width=mw;
    this->height=h;
    FitToScreen();
  }
  else{
    throw std::invalid_argument("cannot open file");    
  }
}

AAtext::~AAtext(){
}
