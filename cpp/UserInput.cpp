#include "class/UserInput.h"

using namespace scgb;
using namespace scgb::Util;

using namespace std;


void UserInput::Draw(){
}

void UserInput::WaitInput(int maxChar,bool isblankok){
  //wgetn_wstr with insertion capability.

  vector<wint_t> container(maxChar);
  int tabsize=4;
  int inspos=0;
  int length=0;
  wint_t tmp;
  auto beg=[&]{return container.begin();};
  auto end=[&]{return container.end();};
  bool cond=false;
  nodelay(window,false);
  wmove(window,0,0);
  auto cursor=GetXY();
  do{
    curs_set(1);
    tmp=GetInput();
    auto kn=key_name(tmp);
    switch(tmp){
    case '\0':
      beep();
      break;
    case '\t':
      if(isblankok && length+tabsize<maxChar){
  	for(int i=0;i<tabsize;i++){
  	  container.insert(inspos+beg(),' ');
  	  inspos++;length++;
  	}
      }
      break;
    case KEY_BACKSPACE:
    case Key::SCGB_BACKSPACE:
      if(inspos>0){
  	inspos--;
  	container.erase(inspos+beg());
	length--;
      }
      break;
    case Key::SCGB_DELETE:
    case Key::SCGB_CTR_D:
      if(inspos+beg()<end()){
	length--;
	container.erase(inspos+beg());
      }
      break;
    case Key::SCGB_RIGHT:
      //move cursor to right
      if(inspos+beg()<end() && inspos<length){
  	inspos++;
      }
      break;
    case Key::SCGB_LEFT:
      //move cursor to left
      if(inspos>0){
  	inspos--;
      }
      break;
    case '\n':
    case '\r':
      cond=true;
      break;
    default:
      if(kn[0]=='^')
	beep();
      else{
  	if((inspos+beg())!=end() && length<maxChar){
  	  container.insert(inspos+beg(),tmp);
  	  inspos++;
  	  length++;
  	}
  	else
  	  beep();
      }
      break;
    }
    wmove(window,cursor[1],cursor[0]);
    wattron(window,COLOR_PAIR(0));
    wclrtoeol(window);
    for(int i=0;i<length;i++){
      waddwstr(window,make_cChar(container[i],0).chars);
    }
    wattroff(window,COLOR_PAIR(0));
    int move=0;
    for(int i=0;i<inspos;i++){
      move+=wcwidth(container[i]);
    }
    wmove(window,cursor[1],cursor[0]+move);
    curs_set(1);
    wrefresh(window);
  }while(!cond);
  
  for(int i=0;i<length;i++){
    data.push_back(container[i]);
  }
  nodelay(window,true);
  curs_set(0);
}

vector<wchar_t> UserInput::GetData(){
  return data;
}

UserInput::UserInput(int x,int y,int w,int h)
  :Movable(x,y,w,h)
{}

void UserInput::WindowSetting(){
  keypad(window,true);
}

UserInput::~UserInput(){
  endwin();
  wcout<<"did this"<<endl;
  for(auto c:data){
    wcout<<c;
  }
  wcout<<endl;
}
