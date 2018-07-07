#include <locale>
#include "Screen.h"
#include "Color.hh"

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
}
