#pragma once
#include <curses.h>
#include <locale>
#include <map>
#include <string>
#include <cmath>

namespace scgb{
  class CursesManager{
    // Manage curses. It's Singleton.
  private:
    CursesManager(std::string locale=""){
      Init(locale);
    }
   
    void Init(std::string locale){
      std::locale::global(std::locale(locale.c_str()));
      initscr();//initialize ncurses
      if(has_colors()){
	start_color();
	for(int i=1;i<COLOR_PAIRS;i++){
	  init_pair(i,0,i);
	}
	if(can_change_color()){
	  int step=51;
	  int count=8;
	  for(int r=0;r<256;r+=step){
	    for(int g=0;g<256;g+=step){
	      for(int b=0;b<256;b+=step){
		init_color(count,r*1000/255.0,g*1000/255.0,b*1000/255.0);
		count++;
	      }
	    }
	  }
	}
      }
      nodelay(stdscr,true);
      keypad(stdscr,true);
      curs_set(0);
      noecho();
      cbreak();
      refresh();
    }
    
  public:
    ~CursesManager(){
      endwin();
    }
    // disable constructers
    CursesManager(CursesManager &cm)=delete;
    void operator=(const CursesManager cm)=delete;
    
    static CursesManager& GetInstance(std::string locale=""){
      static CursesManager instance(locale);
      return instance;
    }
    
    void OnResize(){
      	def_prog_mode();
	endwin();
	initscr();
	reset_prog_mode();
    }
    void Refresh(){
      refresh();
    }
  };
}


/*
  I assume that default curses color macros
  (COLOR_BLACK to COLOR_WHITE) are 0~7.
  At least, ncurses and PDcurses are using these numbers.

  With PDCurses on Windows, init_color() cannot change
  more than 16 color definitions.
  However, the default pallete of PDCurses is exactly the same
  thing as the colors I am tring to set right here.
  Hence you don't need to worry about colors
  if you stick with the normal 256 colors.
*/
