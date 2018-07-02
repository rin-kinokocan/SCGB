#include "class/BaseWindow.h"
#include "class/WindowContainer.h"
using namespace scgb;
using namespace scgb::Util;
using namespace std;

void BaseWindow::InitDraw(){
  MoveCursor(0,0);
  virtualX=x;
  virtualY=y;
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
  int rx=virtualX,ry=virtualY;
  bool flag=false;
  if(rx-x+w<width){
    rx+=w;
  }
  else{
    rx=x;
    ry++;
    flag=true;
 }
  MoveCursor(rx-x,ry-y);
  return flag;
}

void BaseWindow::MoveCursor(int px,int py){
  //moves virtual cursors to the given coods.
  //parameters are relative cursor pos.
  
  if(px>=0 && px<width && py>=0 && py<height){
    int vx=px+x,vy=py+y;
    virtualX=vx;virtualY=vy;
    auto a=psd->GetMaxXY();
    if(DrawPolicy(0)){
      if(x<0)
	px+=x;
      if(y<0)
	py+=y;
      move(py,px);
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
  //returns if virtual cursors are inside of drawing range.
  auto a=psd->GetMaxXY();
  int vx=virtualX-x,vy=virtualY-y;
  if(vx>=0 && vx+w<a[0] && vy>=0 && vy<a[1])
    return true;
  else
    return false;
}

void BaseWindow::OnResize(){}

void BaseWindow::Hide(){
  isHidden=true;
}

void BaseWindow::Show(){
  isHidden=false;
}

BaseWindow::BaseWindow(int x,int y,int w,int h,SizeData* psd)
  :Drawable(x,y,w,h,psd){
}

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

