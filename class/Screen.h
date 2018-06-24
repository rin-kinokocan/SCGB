#pragma once
#include "WindowContainer.h"

namespace scgb{
  class Screen:public WindowContainer{
    //initializes ncurses and creates a window.
  public:
    void Draw();
    void OnResize();
    void Refresh();
    void Init();//The most important method.
    
    //methods to save screen.
    static cchar_t GetCchar(int x,int y);
    static void AddCchar(cchar_t,unsigned int x,unsigned int y);
    Screen():
      WindowContainer(0,0,0,0,nullptr){
      Init();
      int w,h;getmaxyx(stdscr,h,w);
      sd=SizeData(0,0,w,h);
    };

  private:
    //Signal handlers
    static void ResizeHandler(int param);
    static void InterruptHandler(int param);
  };
}
