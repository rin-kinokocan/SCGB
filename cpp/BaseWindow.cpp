#include "class/BaseWindow.h"
#include "class/WindowContainer.h"
using namespace scgb;
using namespace scgb::Util;
using namespace std;

void BaseWindow::InitDraw(){
  MoveCursor(0,0);
  werase(this->window);
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
    wattron(window,attr);
    waddwstr(window,c.chars);
    wattroff(window,attr);
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
  // string info;
  //   info="ADC:";info+=std::to_string(px);
  //   info+=",";info+=std::to_string(py);
  //   Util::LogToStdout(info);

  if(px>=0 && px<width && py>=0 && py<height){
    int vx=px+x,vy=py+y;
    virtualX=vx;virtualY=vy;
    auto a=psd->GetMaxXY();
    if(DrawPolicy(0)){
      if(x<0)
	px+=x;
      if(y<0)
	py+=y;
      wmove(window,py,px);
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


bool BaseWindow::MakeWindow(){
  //Makes a window that fit to the coods&size.
  if(!isHidden){
    int resx=this->width,resy=this->height;
    auto max=psd->GetMaxXY();
    if(x+width > max[0])//too right
      resx=max[0]-x;
    else if(x<0)//too left
      resx=width+x;
    if(y+height>max[1])//too down
      resy=max[1]-y;
    else if(y<0)//too high
      resy=height+y;

    if(resx>0 && resy>0){
      int tx=x,ty=y;
      if(this->x<0)
	tx=0;
      if(this->y<0)
	ty=0;

      if(this->window!=nullptr)
	delwin(this->window);
      this->window=newwin(resy,resx,ty,tx);
    }
    else{
      delwin(window);
      this->window=nullptr;
      return false;
    }
    WindowSetting();
    return true;
  }
  return false;
}

void BaseWindow::OnResize(){
  MakeWindow();  
}

void BaseWindow::Hide(){
  delwin(window);
  window=nullptr;
  isHidden=true;
}

void BaseWindow::Show(){
  isHidden=false;
  MakeWindow();
}

void BaseWindow::Refresh(){
  touchwin(window);
  wnoutrefresh(window);
}

BaseWindow::BaseWindow(int x,int y,int w,int h,SizeData* psd)
  :Drawable(x,y,w,h,psd){}

void BaseWindow::rmove(){
  this->x++;
  MakeWindow();
}

void BaseWindow::lmove(){
  this->x--;
  MakeWindow();
}

void BaseWindow::umove(){
  this->y--;
  MakeWindow();
}

void BaseWindow::dmove(){
  this->y++;
  MakeWindow();
}

