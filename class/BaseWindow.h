#pragma once
#include "DrawingComponent.hpp"
#include "Movable.h"

namespace scgb{
  class BaseWindow :public DrawingComponent{
    //contains fundamental drawing methods.
    //Draw charcters only in its Drawing rectangle.
  private:
    //vartial cursor position
    //relative to up left of Drawing rectangle
    int curx=0;
    int cury=0;
    bool MoveCursor(int x,int y);
    void MoveAfterDraw(int w);
    void DrawTransparent(wchar_t c=L' ');
  protected:
    int x,y,width,height;
    void InitDraw(int x,int y);
    Vector2D GetCursorPos();
    //check the cursor position
    bool IsCursorOnScreen(int w);
    bool IsCursorInBoundary(int x,int y);
    //Drawing methods
    void AddChar(wchar_t c,attr_t a);
    void AddChar(wchar_t c,attr_t a,int x,int y);
    void AddStr(std::wstring c,attr_t a);
    void AddStr(std::wstring c,attr_t a,int x,int y);
    void AddNewLine();
    BaseWindow(int w,int h):DrawingComponent(){width=w;height=h;}
    virtual ~BaseWindow(){}
  };
}
