#pragma once
#include <curses.h>
#include <locale>
#include "InputMap.hpp"

static inline int conv(int x){
  return x*1000/255.0;
}

namespace scgb{
  class Root{
    // Updates curses.
  private:
    bool isend=false;
  public:
    bool IsEnd(){
      return isend;
    }

    void Delete(){
      erase();
    }
    
    void Update(InputMap &im){
      im.Update();
      if(im.GetBool(KEY_RESIZE)){
	def_prog_mode();
	endwin();
	initscr();
	reset_prog_mode();
      }
      if(im.GetBool('q')){
	isend=true;
      }
      refresh();
    }

    void Init(std::string locale=""){
      std::locale::global(std::locale(locale.c_str()));
      initscr();//initialize ncurses
      nodelay(stdscr,true);
      keypad(stdscr,true);
      curs_set(0);
      noecho();
      cbreak();
      
      //color initialization
      if(!has_colors()){
	start_color();
	int i=8;
	if(COLORS>256 && can_change_color()){
	  for(int r=0;r<=255;r+=51){
	    for(int g=0;g<=255;g+=51){
	      for(int b=0;b<=255;b+=51){
		init_color(i,conv(r),conv(g),conv(b));
		i++;
	      }
	    }
	  }
	}
      }
      
      refresh();
    }

    void End(){
      endwin();
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
