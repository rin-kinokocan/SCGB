#include "AAtext.h"
#include <locale>
#include <unistd.h>
#include <string>

using namespace scgb;
void AAtext::Draw(int x,int y){
  InitDraw(x,y);
  for(auto c:data){
    if(c!=L'\n'){
      AddChar(c,0);
    }
    else{
      auto a=GetCursorPos();
      if(a[0]!=width)
	AddNewLine();
    }
  }
}

AAtext::AAtext(std::string filename)
  :BaseWindow(0,0){
  WFile file(filename,std::ios::binary);
  file.imbue(std::locale("ja_JP.UTF-8"));  
  if(file.is_open()!=false){
    file.clear();
    file.seekg(0,std::ios::beg);
    int w=0,h=0,mw=0;
    wchar_t c;
    while(file.get(c)){
      switch(c){
      case L'\n':
	h++;
	if(w>mw)
	  mw=w;
	w=0;
	break;
      default:
	w+=mk_wcwidth(c);
	break;
      }
      data.push_back(c);
    }
    file.close();
    this->width=mw+1;
    this->height=h;
  }
  else{
    throw std::invalid_argument("cannot open file");    
  }
}
