#include "BaseWindow.hpp"
using namespace scgb;
using namespace scgb::Util;
using namespace std;

void BaseWindow::InitDraw(int x,int y){
  this->x=x;this->y=y;
  MoveCursor(0,0);
}

void BaseWindow::AddChar(wchar_t ch,attr_t attr){
  int a=mk_wcwidth(ch);
  if(IsCursorOnScreen(a)){
    std::wstring str(1,ch);
    cchar_t c;
    setcchar(&c,str.c_str(),0,0,nullptr);
    attron(attr);
    add_wchnstr(&c,1);
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

void BaseWindow::DrawTransparent(){
  //draw same thing as already on stdscr.
  cchar_t cch;
  attr_t attr;
  wchar_t wch;
  in_wch(&cch);
  getcchar(&cch,&wch,&attr,nullptr,nullptr);  
  AddChar(wch,attr);
}

bool BaseWindow::MoveCursor(int px,int py){
  //move cursor to given coordinate.
  if(IsCursorInBoundary(px,py)){
    curx=px;
    cury=py;
    move(cury+y,curx+x);
    return true;
  }
  else 
    return false;
}

void BaseWindow::MoveAfterDraw(int w){
  //move cursor position according to given width
  if(curx+w<width){
    MoveCursor(curx+w,cury);
  }
  else if(cury+1<height){
    MoveCursor(0,cury+1);
  }
}

Vector2D BaseWindow::GetCursorPos(){
  Vector2D a(curx,cury);
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
  //returns if cursors are inside of the drawing box
  //after moved to given coordinate.
  if(x<width && y<height && x>=0 && y>=0)
    return true;
  else
    return false;
}
