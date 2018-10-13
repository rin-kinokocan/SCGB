#include "BaseWindow.h"
using namespace scgb;
using namespace scgb::Util;
using namespace std;

void BaseWindow::InitDraw(){
  MoveCursor(0,0);
  curx=0;
  cury=0;
}

bool BaseWindow::AddChar(cChar c){
  //adds cChar where the virtual cursors are.
  //will not draw newline.
  auto ch=cCharToWchar(c);
  auto attr=cCharToAttr(c);
  int a=wcwidth(ch);
  if(ch!='\n' && DrawPolicy(a)){
    attron(attr);
    addwstr(c.chars);
    attroff(attr);
 }
  return MoveAfterDraw(a);
}

bool BaseWindow::MoveAfterDraw(int w){
  int rx=curx,ry=cury;
  bool flag=false;
  if(rx+w<width){
    rx+=w;
  }
  else{
    rx=0;
    ry++;
    flag=true;
 }
  MoveCursor(rx,ry);
  return flag;
}

void BaseWindow::MoveCursor(int px,int py){
  //moves virtual cursors to the given coods.
  //parameters are relative cursor pos.
  if(px>=0 && px<width && py>=0 && py<height){
    curx=px;cury=py;
    if(DrawPolicy(0)){
      move(py+y,px+x);
    }
  }
}

void BaseWindow::AddChar(cChar c,int x,int y){
  MoveCursor(x,y);
  AddChar(c);
}

void BaseWindow::AddStr(std::vector<cChar> data,int x,int y){
  MoveCursor(x,y);
  for(auto a:data){
    AddChar(a);
  }
}

bool BaseWindow::DrawPolicy(int w){
  //returns if cursors are inside of stdscr.
  auto a=GetMaxScrXY();
  int vx=curx+x,vy=cury+y;
  if(vx>=0 && vx+w<a[0] && vy>=0 && vy<a[1])
    return true;
  else
    return false;
}

BaseWindow::BaseWindow(int x,int y,int w,int h)
  :DrawingComponent(x,y,w,h){}

void BaseWindow::rmove(){
  this->x++;
}

void BaseWindow::lmove(){
  this->x--;
}

void BaseWindow::umove(){
  this->y--;
}

void BaseWindow::dmove(){
  this->y++;
}

