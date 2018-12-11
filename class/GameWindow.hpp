#pragma once
#include "CompoundController.hpp"

namespace scgb{
  // Work as a controller.
  // Contains other controllers, and update them every frame.
  class GameWindow:public CompoundController{
  public:
    void Draw(){
      erase();
      for(auto c:cs){
	c.second->Draw();
      }
      refresh();
    }
    
    void Exec(InputMap im){
      im.Update();
      if(im.GetBool(KEY_RESIZE)){
	def_prog_mode();
	endwin();
	initscr();
	reset_prog_mode();
      }
      for(auto c:cs){
	c.second->Exec(im);
      }
      if(im.GetBool('q')){
	SendMessage(EVE_END);
      }
    }

    GameWindow(std::string locale){
      setlocale(LC_ALL, locale.c_str());
      initscr();//initialize ncurses
      nodelay(stdscr,true);
      keypad(stdscr,true);
      curs_set(0);
      noecho();
      cbreak();
      //color initialization
      Color::Init();
      refresh();
    }
    GameWindow():GameWindow(""){}
    ~GameWindow(){
      endwin();
    }
  };
}
