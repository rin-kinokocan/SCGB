#include <ncurses.h>
#include <csignal>
#include <unistd.h>
#include <locale>
#include "../class/Screen.h"

using namespace scgb;

void Screen::Init(int width,int height){//sets WINDOW pointer
  this->window=newwin(height,width,0,0);
}

void Screen::Draw(){
  box(this->window,0,0);
  int x,y;
  getmaxyx(this->window,y,x);      
  mvwprintw(this->window,0,1,"size: %d %d",x,y);
  
  for(auto& i:this->drawentity){   
    i.second->Draw();
    mvwprintw(this->window,1,1,"printing somethig...");
  }
  
  mvwprintw(this->window,3,1,"%dcolors available",COLORS);
  mvwprintw(this->window,4,1,"%dcolor-pairs available",COLOR_PAIRS);
  wmove(this->window,5,0);
  
  for(int i=0;i<COLORS;i++){
    wattron(this->window,COLOR_PAIR(i));
    wprintw(this->window,"i");
    wattroff(this->window,COLOR_PAIR(i));
  }
}


void Screen::Refresh(){
  touchwin(stdscr);
  touchwin(this->window);
  wnoutrefresh(stdscr);
  wnoutrefresh(this->window);
  for(auto& i:this->drawentity){   
    i.second->Refresh();
  }
  doupdate();
}

void Screen::GetProperty(int ary[]){  
}

void Screen::Destroy(){
  mvwprintw(this->window,2,1,"destroy is called ");  
  this->state=STA_DESTROY;
}

void Screen::Resize(){
  endwin();
  initscr();
  for(auto& i:this->drawentity){
    i.second->Resize();
    i.second->Refresh();
  }
  mvwprintw(this->window,10,0,"resizing...");
  wnoutrefresh(this->window);
  werase(this->window);
  doupdate();
}

Event Screen::GetEvent(){
  return  (Event)getch();
}


State Screen::GetState(){
  return this->state;  
}

Screen::Screen(int width,int height){//Initialize everything.
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
  this->palette.reset(new Color());
  this->Init(width,height);
  this->state=STA_OPEN;
  this->width=width;
  this->height=height;
  //if ncurses hasn't enabled sigwinch.
  signal(SIGWINCH,this->SigHandler);
}



Screen::~Screen(){
  this->drawentity.clear();
  delwin(this->window);
  endwin();//ends ncurses
  printf("\nend\n");
}

void Screen::SigHandler(int param){//my ncurses hasn't enabled sigwinch
  if(isendwin()==false){
    ungetch(scgb::EVE_RESIZE);
  }
}
