#pragma once
#include "GameWindow.h"
#include "../include/define.h"
#include "Color.hh"

namespace scgb{

  class Screen :public GameWindow{
    //initializes ncurses and creates a window.

  private:
    State state;
    void Init(int width,int height);
  public:
    Palette palette;
    
    Screen(int width,int height);
    void Draw();
    void Refresh();
    void Destroy();
    void Resize();
    void GetProperty(int ary[]);

    Event GetEvent();    
    State GetState();
    ~Screen();

    //for xterm version only?
    static void SigHandler(int param);
  };

}
