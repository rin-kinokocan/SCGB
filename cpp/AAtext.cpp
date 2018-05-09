#include "../class/AAtext.h"
#include <locale>
#include <unistd.h>
#include <unicode/utypes.h>
#include <string>

using namespace scgb;

void AAtext::Draw(){
  InitDraw();
  this->file.clear();
  this->file.seekg(0,std::ios::beg);
  Vector2D cur;
  Vector2D max;
  int d;
  for(wchar_t c;file.get(c);){
    cur=GetXY();
    max=GetMaxXY();
    d=max[0]-cur[0]-1;
    int w=wcwidth(c);
    switch(c){
    case L' ':
    case L'　':
      DrawTransparent(w);
      break;
    case L'\n':
      for(int i=0;i<d;i++)
	DrawTransparent(1,true);
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
  cchar_t b;
  b.chars[0]='\n';b.chars[1]='\0';
  b.attr=0;
  AddChar(b);
}

void AAtext::Refresh(){
  touchwin(window);
  wnoutrefresh(window);
}

AAtext::AAtext(int x,int y,std::string filename)
  :file(filename,std::ios::binary){
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
    }
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
  file.close();
}
