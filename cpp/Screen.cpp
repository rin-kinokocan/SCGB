#include <locale>
#include "Screen.h"
#include "Color.hh"

using namespace std;
using namespace scgb;

void Screen::Refresh(){
  if(!isendwin()){
    wnoutrefresh(stdscr);
    doupdate();
  }  
}

void Screen::OnResize(){
  def_prog_mode();
  endwin();
  initscr();
  reset_prog_mode();
}


void Screen::Init(){//Initialize everything.
  setlocale(LC_ALL, "");
  initscr();//initialize ncurses
  nodelay(stdscr,true);
  keypad(stdscr,true);
  curs_set(0);
  noecho();
  cbreak();
  //color initialization
  Color::Init();
}
