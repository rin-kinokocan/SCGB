#pragma once
#include "WindowContainer.h"

namespace scgb{
  class Screen:public WindowContainer{
    //initializes ncurses and creates a window.
  public:
    Vector2D GetMaxXY();
    void Draw();
    void OnResize();
    void Destroy();
    void Refresh();
    cChar GetWholeScreen(int x,int y);
    void AddWholeScreen(int x,int y,cChar c);
    
    //methods to this class
    Event GetEvent();    
    State GetState();
    void Init();//The most important method.
    
    //methods to save screen.
    static cchar_t GetCchar(int x,int y);
    static void AddCchar(cchar_t,unsigned int x,unsigned int y);
    Screen():
      WindowContainer(0,0,0,0){};

  private:
    //static variables
    std::vector<cchar_t> wholeScreen;
    static State state;
    //Signal handlers
    static void ResizeHandler(int param);
    static void InterruptHandler(int param);
  };
}
