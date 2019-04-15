#include "define.hpp"
#include <iostream>
#include <curses.h>
#include <unistd.h>

namespace scgb{
  namespace Util{
    Vector2D GetMaxScr(){
      Vector2D v;
      getmaxyx(stdscr,v[1],v[0]);
      return v;
    }
    
    void LogToStdout(std::string a){
      bool f=true;
      if(isendwin())
      	f=false;
      else
	endwin();
      std::cout<<a<<std::endl;
      if(f)
	initscr();
    }
    void ShowColorPairs(){
      erase();
      for(int i=0;i<COLOR_PAIRS;i++){
	attron(COLOR_PAIR(i));
	addch('T');
	attroff(COLOR_PAIR(i));
      }
      refresh();
      sleep(3);
    }
  }
}
