#include <ncurses.h>
#include <csignal>
#include <unistd.h>
#include <locale>
#include "../class/define.h"
#include "../class/Drawable.h"
#include "../class/Screen.h"
#include "../class/Color.hh"

using namespace scgb;

State Screen::state;
DrawList Screen::drawentity;
vector<cchar_t> Screen::wholeScreen;

void Screen::Draw(){
  int x,y;
  getmaxyx(stdscr,y,x);      
  mvprintw(0,1,"size: %d %d",x,y);
  mvwprintw(stdscr,3,1,"%dcolors available",COLORS);
  mvwprintw(stdscr,4,1,"%dcolor-pairs available",COLOR_PAIRS);
  wmove(stdscr,5,0);
  for(int i=0;i<COLORS;i++){
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
    mvprintw(1,1,"printing somethig...");
  }
}


void Screen::Refresh(){
  touchwin(stdscr);
  wnoutrefresh(stdscr);
  for(auto& i:Screen::drawentity){   
    i.second->Refresh();
  }
  doupdate();
}

void Screen::Destroy(){
  mvprintw(2,1,"destroy is called ");
  Screen::drawentity.clear();
  endwin();//ends ncurses
  Screen::state=STA_DESTROY;
}

void Screen::Resize(){
  endwin();
  initscr();
  for(auto& i:Screen::drawentity){
    i.second->Resize();
    i.second->Refresh();
  }
  mvprintw(10,0,"resizing...");
  doupdate();
}

Event Screen::GetEvent(){
  return  (Event)getch();
}


cchar_t Screen::GetCchar(int x,int y){
  int my,mx;getmaxyx(stdscr,my,mx);
  if(x>mx || y>my)
    throw std::invalid_argument("overflow");
  return Screen::wholeScreen[x+y*mx];
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
  start_color();
  use_default_colors();
  Color::Init();
  //initialization of static variables.
  int x,y;getmaxyx(stdscr,y,x);
  Screen::state=STA_OPEN;
  Screen::wholeScreen.resize(x*y);
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
  Screen::Destroy();
}
