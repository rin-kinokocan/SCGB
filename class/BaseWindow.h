#pragma once
#include "Drawable.h"

namespace scgb{
  class BaseWindow :public Drawable{
  private:
    //virtual cursors.
    //shows where the cursors globally are.
    //I call relative coodinates
    //((0,0) at left top of the window) local.
    int virtualX;
    int virtualY;
  protected:
    //coordinates of the window.
    //unlike curses' window coodinates,
    //these can be negative.
    //virtualX-x=relative cursor pos.
    WinPtr window=nullptr;
    bool isHidden=false;
    bool MakeWindow();   
    void InitDraw();
    bool MoveAfterDraw(int w);
    bool AddChar(cChar c);//for file reading things,I guess?
    bool DrawPolicy(int w);
    virtual void WindowSetting(){};
  public:
    void Refresh();
    virtual void OnResize();
    virtual void Hide();
    virtual void Show();
    //Movable implementations
    virtual void rmove();
    virtual void lmove();
    virtual void umove();
    virtual void dmove();
    //Drawing methods
    void MoveCursor(int x,int y);
    void AddChar(cChar c,int x,int y);//for normal use.
    void AddStr(std::vector<cChar>,int x,int y);//to add string.
    
    BaseWindow(int,int,int,int,SizeData*);
    virtual ~BaseWindow(){delwin(window);};
  };
  
  class BWBuilder:public DrawableBuilder{
  public:
    virtual Drawable* GetResult(){
      return new BaseWindow(x,y,w,h,psd);
    };
    BWBuilder(int x,int y,int w,int h)
      :DrawableBuilder(x,y,w,h){};
    virtual ~BWBuilder(){};
  };
}
