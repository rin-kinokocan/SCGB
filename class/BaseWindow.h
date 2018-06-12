#pragma once
#include "Drawable.h"
#include "WindowContainer.h"

namespace scgb{
  class BaseWindow :public Drawable{
  private:
    int virtualX;
    int virtualY;
  protected:
    int width;
    int height;
    int x;
    int y;
    WinPtr window=nullptr;
    bool isHidden=false;
   
    void InitDraw();
    void AfterDraw(cChar c);
    void OnReturn();
    void AddChar(cChar c);//for file reading things,I guess?
    void DrawTransparent(int w,bool f=false);
    bool DrawPolicy(int w);
    bool FitToScreen();
    virtual void WindowSetting(){};
  public:
    virtual void OnResize();
    virtual void Hide();
    virtual void Show();
    virtual void DrawOnScreen();
    
    void AddChar(cChar c,int x,int y);//for normal use.
    void AddStr(std::vector<cChar>,int x,int y);//to add string.
    Vector2D GetGlobalCursorPos();
    Vector2D GetGlobalCursorPos(int x,int y);
    Vector2D GetXY();
    Vector2D GetMaxXY();
    Vector2D GetVirtualCursorPos();
    cChar GetWholeScreen(int x,int y);
    void AddWholeScreen(int x,int y,cChar c);
    void Refresh();
    BaseWindow(){};
    BaseWindow(int,int,int,int);
    virtual ~BaseWindow(){delwin(window);};
  };
}
