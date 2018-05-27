#include <csignal>
#include <locale>
#include "class/Screen.h"
#include "class/Color.hh"

using namespace std;
using namespace scgb;

State Screen::state;
std::map<int,scgb::pDrawable> Screen::drawentity;
vector<cchar_t> Screen::wholeScreen;

void Screen::DeleteDrawable(int l){
  auto a=Screen::drawentity.find(l);
  if(a!=Screen::drawentity.end()){
    Screen::drawentity.erase(a);
  }
}

void Screen::Draw(){
  int x,y;
  erase();
  getmaxyx(stdscr,y,x);      
  mvprintw(0,1,"size: %d %d",x,y);
  mvwprintw(stdscr,3,1,"%dcolors available",COLORS);
  mvwprintw(stdscr,4,1,"%dcolor-pairs available",COLOR_PAIRS);
  wmove(stdscr,5,0);
  for(int i=1;i<=COLORS;i++){
    wattron(stdscr,COLOR_PAIR(i));
    wprintw(stdscr,"i");
    wattroff(stdscr,COLOR_PAIR(i));
  }
  for(auto &a:Screen::wholeScreen){//initialize wholescreen
    a.chars[0]=L' ';
    a.chars[1]=L'\0';
    a.attr=0;
  }
  for(auto i:Screen::drawentity){
    i.second->Draw();
    i.second->DrawOnScreen();
  }
}


void Screen::Refresh(){
  if(isendwin()==false){
    touchwin(stdscr);
    wnoutrefresh(stdscr);
    for(auto& i:Screen::drawentity){   
      i.second->Refresh();
    }
    doupdate();touchwin(stdscr);
    wnoutrefresh(stdscr);
    for(auto& i:Screen::drawentity){   
      i.second->Refresh();
    }
    doupdate();
  }  
}

void Screen::Destroy(){
  mvprintw(2,1,"destroy is called ");
  Screen::drawentity.clear();
  Screen::state=STA_DESTROY;
}

void Screen::Resize(){
  endwin();
  initscr();
  auto a=GetMaxXY();
  Screen::wholeScreen.resize(a[0]*a[1]);
  for(auto& i:Screen::drawentity){
    i.second->Resize();
    i.second->Refresh();
  }
  mvprintw(10,0,"resizing...");  
}

Event Screen::GetEvent(){
  return  (Event)getch();
}

Vector2D Screen::GetMaxXY(){
  int x,y;getmaxyx(stdscr,y,x);
  Vector2D v;
  v.resize(2);
  v[0]=x;v[1]=y;
  return v;
}

cchar_t Screen::GetCchar(int x,int y){
  auto a=Screen::GetMaxXY();
  if(x>a[0] || x<0 || y>a[1] || y<0){
    throw std::exception();
  }
  return Screen::wholeScreen[x+y*a[0]];
}

void Screen::AddCchar(cchar_t c,unsigned int x,unsigned int y){
  unsigned int my,mx;getmaxyx(stdscr,my,mx);
  if(x>mx || y>my)
    return;
  int pos=x+y*mx;
  Screen::wholeScreen[pos]=c;
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
  auto max=Screen::GetMaxXY();
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
