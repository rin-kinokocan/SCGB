#include <csignal>
#include <locale>
#include "class/Screen.h"
#include "class/Color.hh"

using namespace std;
using namespace scgb;

State Screen::state;
void Screen::Draw(){
  int x,y;
  erase();
  for(auto &a:Screen::wholeScreen){//initialize wholescreen
    a=Util::make_cChar('\0',0);
  }
  for(auto i:drawentity){
    i.second->Draw();
    i.second->DrawOnScreen();
  }
}

void Screen::Refresh(){
  if(isendwin()==false){
    touchwin(stdscr);
    wnoutrefresh(stdscr);
    for(auto& i:drawentity){   
      i.second->Refresh();
    }
    doupdate();touchwin(stdscr);
    wnoutrefresh(stdscr);
    for(auto& i:drawentity){   
      i.second->Refresh();
    }
    doupdate();
  }  
}

cChar Screen::GetWholeScreen(int x,int y){
  auto a=GetMaxXY();
  if(x>a[0] || x<0 || y>a[1] || y<0){
    throw std::exception();
  }
  return Screen::wholeScreen[x+y*a[0]];
}

void Screen::AddWholeScreen(int x,int y,cChar c){
  unsigned int my,mx;getmaxyx(stdscr,my,mx);
  if(x>mx || y>my)
    return;
  int pos=x+y*mx;
  Screen::wholeScreen[pos]=c;
}

void Screen::Destroy(){
  mvprintw(2,1,"destroy is called ");
  drawentity.clear();
  Screen::state=STA_DESTROY;
}

void Screen::OnResize(){
  endwin();
  initscr();
  auto a=GetMaxXY();
  Screen::wholeScreen.resize(a[0]*a[1]);
  for(auto& i:drawentity){
    i.second->OnResize();
    i.second->Refresh();
  }
  mvprintw(10,0,"resizing...");  
}

Event Screen::GetEvent(){
  return  (Event)getch();
}

Vector2D Screen::GetMaxXY(){
  return Util::GetMaxScrXY();
}

State Screen::GetState(){
  return Screen::state;  
}

void Screen::Init(){//Initialize everything.
  setlocale(LC_ALL, "");
  initscr();//initialize ncurses
  nodelay(stdscr,true);
  keypad(stdscr,true);
  curs_set(0);
  noecho();
  raw();
  cbreak();
  //color initialization starts!
  Color::Init();
  //initialization of static variables.
  auto max=GetMaxXY();
  Screen::state=STA_OPEN;
  Screen::wholeScreen.resize(max[0]*max[1]);
  //if ncurses hasn't enabled sigwinch.
  signal(SIGWINCH,Screen::ResizeHandler);
  //to detect Ctrl-c
 signal(SIGQUIT,Screen::InterruptHandler);
}

void Screen::ResizeHandler(int param){
  //I hasn't enabled sigwinch
  if(isendwin()==false){
    ungetch(scgb::EVE_RESIZE);
  }
}

void Screen::InterruptHandler(int param){
  Screen::state=STA_DESTROY;
}
