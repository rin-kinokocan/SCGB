#pragma once
#include "Color.hpp"
#include "DCHandler.hpp"
#include "LogicComponent.hpp"
#include "ELHandler.hpp"

namespace scgb{
  class GameWindow:public LogicComponent,public ELHandler{
  protected:
    std::map<int,std::shared_ptr<DCHandler>> dchs;
  public:
    void Draw(){
      erase();
      for(auto dch:dchs){
	dch.second->Draw();
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
      for(auto a:dchs){
	a.second->Exec(im);
      }
      if(im.GetBool('q')){
	SendMessage(EVE_END);
      }
    }

    void AddDCHandler(int l,std::shared_ptr<DCHandler> dch){
      dchs[l]=dch;
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
    }
    GameWindow():GameWindow(""){}
    ~GameWindow(){
      endwin();
    }
  };
}
