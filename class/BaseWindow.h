#pragma once
#include "define.h"
#include "Drawable.h"

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

    void InitDraw();
    void AfterDraw(cChar c);
    void OnReturn();
    void AddChar(cChar c,bool useBelow=false);
    void DrawTransparent(int w,bool f=false);
    bool DrawPolicy(int w);
    bool FitToScreen();
  public:
    void Resize();
    void DrawOnScreen();
    Vector2D GetGlobalCursorPos();
    Vector2D GetGlobalCursorPos(int x,int y);
    Vector2D GetXY();
    Vector2D GetMaxXY();
    Vector2D GetVirtualCursorPos();
    void Refresh();
    
    BaseWindow(){};
    BaseWindow(int,int,int,int);
    virtual ~BaseWindow(){};
  };
}
