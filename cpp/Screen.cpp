#include <csignal>
#include <locale>
#include "class/Screen.h"
#include "class/Color.hh"

using namespace std;
using namespace scgb;

void Screen::Draw(){
  for(auto i:drawentity){
    i.second->Draw();
  }
}

void Screen::Refresh(){
  if(!isendwin()){
    for(auto& i:drawentity){
      i.second->Refresh();
    }
    wnoutrefresh(stdscr);
    doupdate();
  }  
}

void Screen::OnResize(){
  endwin();
  initscr();
  for(auto& i:drawentity){
    i.second->OnResize();
    i.second->Refresh();
  }
  mvprintw(10,0,"resizing...");  
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
}

