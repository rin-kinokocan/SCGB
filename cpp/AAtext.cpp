#include "class/AAtext.h"
#include <locale>
#include <unistd.h>
#include <unicode/utypes.h>
#include <string>

using namespace scgb;

void AAtext::Draw(){
  InitDraw();
  for(auto c:data){
    // int w=wcwidth(c);
    switch(c){
    case L'\n':
      while(!AddChar(Util::make_cChar(' ',0))){;}
      break;
    case L' ':
    case L'　':
      // for(int i=0;i<w;i++)
      // 	DrawTransparent(1);
      // break;
    default:
      AddChar(Util::make_cChar(c,0));
      break;
    }
  }
  // while(!DrawTransparent(1)){;}
}

AAtext::AAtext(int x,int y,SizeData* psd,std::string filename)
  :BaseWindow(x,y,0,0,psd){
  WFile file(filename,std::ios::binary);
  file.imbue(std::locale("ja_JP.UTF-8"));  
  if(file.is_open()!=false){
    int w=1,h=1,mw=0;
    file.clear();
    file.seekg(0,std::ios::beg);
    wchar_t c;
    while(file.get(c)){
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
    this->x=x;
    this->y=y;
    this->width=mw+1;
    this->height=h;
    MakeWindow();
  }
  else{
    throw std::invalid_argument("cannot open file");    
  }
}
