#include "../class/AAtext.h"
#include <locale>
#include <unistd.h>
#include <unicode/utypes.h>
#include <string>

using namespace scgb;

void AAtext::Draw(){
  wmove(this->window,0,0);
  werase(this->window);
  this->file.clear();
  this->file.seekg(0,std::ios::beg);
  int x=this->x,y=this->y;//where the cursor virtually should be.
  for(wchar_t c;this->file.get(c);){
    int w=wcwidth(c);
    int cx,cy;getyx(this->window,cy,cx);
    int mx,my;getmaxyx(this->window,my,mx);
    if(this->DrawPolicy(x,y,w)){
      switch(c){
      case L' ':
      case L'　':
	this->DrawTransparent(w);
	break;
      case '\n':
	break;
      default:
	cchar_t a;
	a.chars[0]=c;
	a.chars[1]=L'\0';
	a.attr=0;
	auto b=this->GetGlobalCursorPos();
	Screen::AddCchar(a,b[0],b[1]);
	waddwstr(this->window,a.chars);
	break;
      }
    }
    if(c=='\n'){
      if(y>=0){
	for(;cx<mx-1;getyx(this->window,cy,cx)){
	  //if returns,fill the lest with space.
	  this->DrawTransparent(1);
	}
	wmove(this->window,cy+1,0);
      }
      y+=1;
      x=this->x;
    }
    else{
      x+=w;
    }
  }
}

void AAtext::Refresh(){
  touchwin(this->window);
  wnoutrefresh(this->window);
}

void AAtext::DrawTransparent(int w){
  auto b=GetGlobalCursorPos();
    cchar_t a=Screen::GetCchar(b[0],b[1]);
    if(wcwidth(a.chars[0])==w && a.chars[1]=='\0'){
      wattron(this->window,a.attr);
      waddwstr(this->window,a.chars);
      wattroff(this->window,a.attr);
    }
    else{//just in case.
      switch(w){
      case 1:
	wattron(this->window,a.attr);
	waddwstr(this->window,L" ");
	wattroff(this->window,a.attr);
	break;
      case 2:
	for(int i=0;i<2;i++){
	  b=GetGlobalCursorPos();
	  a=Screen::GetCchar(b[0],b[1]);
	  wattron(this->window,a.attr);
	  waddwstr(this->window,L" ");
	  wattroff(this->window,a.attr);
	}
      }
    }
}

int AAtext::DrawPolicy(int x,int y,int w){
  int mx,my;
  getmaxyx(stdscr,my,mx);
  if(x>=0 && x+w<mx && y>=0 && y<my){
    return true;
  }
  else{
    return false;
  }
}


AAtext::AAtext(int x,int y,std::string filename)
  :file(filename,std::ios::binary){
  this->file.imbue(std::locale("ja_JP.UTF-8"));  
  if(this->file.is_open()!=false){
    int w=1,h=1,mw=0;
    this->file.clear();
    this->file.seekg(0,std::ios::beg);
    for(wchar_t c;this->file.get(c);){
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
    this->window=newwin(h-1,mw,y,x);
    this->x=x;
    this->y=y;
    this->width=mw;
    this->height=h-1;
  }
  else{
    throw std::invalid_argument("cannot open file");    
  }
}

AAtext::~AAtext(){
  this->file.close();
}
