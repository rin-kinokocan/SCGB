#pragma once
#include "BaseController.hpp"
#include "InputMap.hpp"
#include "Color.hpp"

namespace scgb{
  // Contains controllers, and update them every frame.
  class GameWindow{
  protected:
    std::vector<std::shared_ptr<BaseController>> controllers;
  public:
    void Draw(){
      erase();
      for(auto& c:controllers){
	c->Draw();
      }
      refresh();
    }

    void Update(InputMap im){
      im.Update();
      if(im.GetBool(KEY_RESIZE)){
	def_prog_mode();
	endwin();
	initscr();
	reset_prog_mode();
      }
      // if(im.GetBool('q')){
      // 	SendMessage(EVE_END);
      // }
      // for(auto c:cs){
      // 	c.second->Exec(im);
      // }
    }

    template <class T>
    std::shared_ptr<T> Append(T* param){
      std::shared_ptr<BaseController> ptr(param);
      controllers.push_back(ptr);
      return std::static_pointer_cast<T>(ptr);
    }

    void Append(std::shared_ptr<BaseController> a){
      controllers.push_back(a);
    }

    GameWindow(std::string locale=""){
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
    ~GameWindow(){
      endwin();
    }
  };
}
