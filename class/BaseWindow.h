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
    WinPtr window;

    void InitDraw();
    void AfterDraw(cChar c);
    void AddChar(cChar c);
    void DrawTransparent(int w,bool f=false);
    bool DrawPolicy(int w);
    bool FitToScreen();
    void DebugInfo();
  public:
    void Resize();
    void DrawOnScreen();
    Vector2D GetGlobalCursorPos();
    Vector2D GetGlobalCursorPos(int x,int y);
    Vector2D GetXY();
    Vector2D GetMaxXY();

    virtual ~BaseWindow(){};
  };
}
