#include "BaseWindow.hpp"
using namespace scgb;
using namespace scgb::Util;
using namespace std;

void BaseWindow::InitDraw(int x,int y){
  this->x=x;this->y=y;
  MoveCursor(0,0);
  curx=0;
  cury=0;
}

void BaseWindow::AddChar(wchar_t ch,attr_t attr){
  int a=mk_wcwidth(ch);
  if(IsCursorOnScreen(a)){
    std::wstring str(1,ch);
    attron(attr);
    addwstr(str.c_str());
    attroff(attr);
  }
  MoveAfterDraw(a);
}

void BaseWindow::AddChar(wchar_t ch,attr_t attr,int x,int y){
  MoveCursor(x,y);
  AddChar(ch,attr);
}

void BaseWindow::AddStr(std::wstring str,attr_t attr){
  for(auto ch:str){
    AddChar(ch,attr);
  }
}

void BaseWindow::AddStr(std::wstring str,attr_t attr,int x,int y){
  MoveCursor(x,y);
  AddStr(str,attr);
}

void BaseWindow::AddNewLine(){
  MoveCursor(0,cury+1);
}

void BaseWindow::DrawTransparent(wchar_t c){
  //use same attribute as already in stdscr.
  cchar_t a;
  in_wch(&a);
  AddChar(c,GetAttr(a));
}

bool BaseWindow::MoveCursor(int px,int py){
  //move cursor to given coodinate.
  if(IsCursorInBoundary(px,py)){
    curx=px;
    cury=py;
    move(y+cury,x+curx);
    return true;
  }
  else 
    return false;
}

void BaseWindow::MoveAfterDraw(int w){
  //move relative cursor position according to given width
  if(curx+w<width){
    MoveCursor(curx+w,cury);
  }
  else if(cury+1<height){
    MoveCursor(0,cury+1);
  }
}

Vector2D BaseWindow::GetCursorPos(){
  Vector2D a;
  a[0]=curx;a[1]=cury;
  return a;
}

bool BaseWindow::IsCursorOnScreen(int w){
  auto m=GetMaxScr();
  if(x+curx<0 || y+cury<0)
    return false;
  if(x+curx+w<m[0] && y+cury<m[1])
    return true;
  else
    return false;
}

bool BaseWindow::IsCursorInBoundary(int x,int y){
  //returns if cursors are inside of the boundary box.
  //after moved to given coodinate.
  if(x<=width && y<=height && x>=0 && y>=0)
    return true;
  else
    return false;
}
