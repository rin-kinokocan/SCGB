#pragma once
#include "Drawable.h"
#include "WindowContainer.h"

namespace scgb{
  class BaseWindow :public Drawable{
  private:
    //virtual cursors.
    //shows where the cursors globally are.
    //I call relative coodinates
    //((0,0) at left top of the window) local.
    int virtualX;
    int virtualY;
    bool MakeWindow();
  protected:
    int width;
    int height;
    //coordinates of the window.
    //unlike curses' window coodinates,
    //these can be negative.
    //virtualX-x=relative cursor pos.
    int x;
    int y;
    WinPtr window=nullptr;
    bool isHidden=false;
   
    void InitDraw();
    bool MoveAfterDraw(int w);
    bool AddChar(cChar c);//for file reading things,I guess?
    bool DrawTransparent(int w,bool f=false);
    bool DrawPolicy(int w);
    virtual void WindowSetting(){};
  public:
    Vector2D GetVirtualCursor();
    cChar GetWholeScreen(int x,int y);
    void AddWholeScreen(int x,int y,cChar c);
    void Refresh();
    virtual void SetParent(WindowContainer* a);
    virtual void OnResize();
    virtual void Hide();
    virtual void Show();
    virtual void DrawOnScreen();
    //Movable implementations
    virtual void rmove();
    virtual void lmove();
    virtual void umove();
    virtual void dmove();
    //Drawing methods
    void MoveCursor(int x,int y);
    void AddChar(cChar c,int x,int y);//for normal use.
    void AddStr(std::vector<cChar>,int x,int y);//to add string.
    //Helpers
    BaseWindow(){};
    BaseWindow(int,int,int,int);
    virtual ~BaseWindow(){delwin(window);};
  };
}
