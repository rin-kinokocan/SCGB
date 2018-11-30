#pragma once
#include "DrawingComponent.hpp"

namespace scgb{
  class BaseWindow :public DrawingComponent{
    //contains fundamental drawing methods.
    //Draw charcters only in its Drawing rectangle.
  private:
    //vartial cursor position
    //relative to up left of Drawing rectangle
    int curx=0;
    int cury=0;
  protected:
    int x,y,width,height;
    //moves cursor
    void InitDraw(int x,int y);
    bool MoveCursor(int x,int y);
    void MoveAfterDraw(int w);
    Vector2D GetCursorPos();
    //check the cursor position
    bool IsCursorOnScreen(int w);
    bool IsCursorInBoundary(int x,int y);
    //Drawing methods
    virtual void AddChar(wchar_t c,attr_t a);
    virtual void AddChar(wchar_t c,attr_t a,int x,int y);
    virtual void AddStr(std::wstring c,attr_t a);
    virtual void AddStr(std::wstring c,attr_t a,int x,int y);
    virtual void AddNewLine();
    virtual void DrawTransparent();
    BaseWindow(int w,int h){width=w;height=h;}
    virtual ~BaseWindow(){}
  };
}
