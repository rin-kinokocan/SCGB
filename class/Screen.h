#pragma once
#include "WindowContainer.h"

namespace scgb{
  class Screen:public WindowContainer{
    //initializes ncurses and creates a window.
  public:
    void Draw();
    void OnResize();
    void Destroy();
    void Refresh();
    
    void Init();//The most important method.
    
    //methods to save screen.
    static cchar_t GetCchar(int x,int y);
    static void AddCchar(cchar_t,unsigned int x,unsigned int y);
    Screen():
      WindowContainer(0,0,0,0,nullptr){};

  private:
    //Signal handlers
    static void ResizeHandler(int param);
    static void InterruptHandler(int param);
  };
}
