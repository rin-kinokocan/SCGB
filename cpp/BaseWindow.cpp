#include "../class/BaseWindow.h"
using namespace scgb;
using namespace std;

void BaseWindow::InitDraw(){
  wmove(this->window,0,0);
  werase(this->window);
  virtualX=x;
  virtualY=y;
};
void BaseWindow::AfterDraw(cChar c){
  auto a=c.chars[0];
  if(a!='\n'){
    virtualX+=wcwidth(c.chars[0]);
  }
  else{
    if(virtualY>=0){
      auto cur=GetXY();
      DrawTransparent(1,true);
      wmove(window,cur[1]+1,0);
    }
    virtualX=x;
    virtualY++;
  }
  DebugInfo();
};
void BaseWindow::DebugInfo(){
  string info;
  move(10,40);
  info="x:"+to_string(x);
  addstr(info.c_str());
  move(11,40);
  info="y:"+to_string(y);
  addstr(info.c_str());
  move(12,40);
  info="width:"+to_string(width);
  addstr(info.c_str());
  move(13,40);
  info="height:"+to_string(height);
  addstr(info.c_str());
  move(14,40);
  auto max=GetMaxXY();
  info="maxwidth:"+to_string(max[0]);
  addstr(info.c_str());
  move(15,40);
  info="maxheight:"+to_string(max[1]);
  addstr(info.c_str());
  move(16,40);
};
void BaseWindow::AddChar(cChar c){
  if(c.chars[1]!='\0')//validation
    return;
  int ch=c.chars[0];
  int a=wcwidth(ch);
  if(ch!='\n' && DrawPolicy(a)){
    auto b=GetGlobalCursorPos();
    wattron(window,c.attr);
    waddwstr(window,c.chars);
    wattroff(window,c.attr);
    Screen::AddCchar(c,b[0],b[1]);
  }
  AfterDraw(c);
};
void BaseWindow::DrawTransparent(int w,bool f){
    auto b=GetGlobalCursorPos();
    auto a=Screen::GetCchar(b[0],b[1]);
    int cw=wcwidth(a.chars[0]);
    if(cw>w || a.chars[1]!='\0'){
      a.chars[0]=' ';
    }
    if(f){
      wattron(window,a.attr);
      waddwstr(window,a.chars);
      wattroff(window,a.attr);
    }
    else
      AddChar(a);
};
bool BaseWindow::DrawPolicy(int w){
  Vector2D max=Screen::GetMaxXY();
  int vx=virtualX,vy=virtualY;
  if(vx>=0 && vx+w<max[0] && vy>=0 && vy<max[1])
    return true;
  else{
    return false;
  }
};
bool BaseWindow::FitToScreen(){
  int resx=this->width,resy=this->height;
  auto max=Screen::GetMaxXY();
  if(x+width > max[0])//too right
    resx=max[0]-x;
  else if(x<0)//too left
    resx=width+x;
  if(y+height>max[1])//too down
    resy=max[1]-y;
  else if(y<0)//too high
    resy=height+y;

  if(window==nullptr && resx>0 && resy>0){
    int tx=x,ty=y;
    if(this->x<0)
      tx=0;
    if(this->y<0)
      ty=0;
    delwin(this->window);
    this->window=newwin(resy,resx,ty,tx);
  }
  if(wresize(this->window,resy,resx)){
    //if cannot create that size of window.(namely too small)
    delwin(this->window);
    this->window=nullptr;
    return false;
  }
  return true;
};

void BaseWindow::DrawOnScreen(){
  auto max=GetMaxXY();
  for(int i=0;i<max[0];i++){
    for(int j=0;j<max[1];j++){
      cChar a;
      mvwin_wch(window,j,i,&a);
      auto b=GetGlobalCursorPos(i,j);
      Screen::AddCchar(a,b[0],b[1]);
    }
  }
};

void BaseWindow::Resize(){
  FitToScreen();
};
    
Vector2D BaseWindow::GetGlobalCursorPos(){
  int posx,posy;getbegyx(this->window,posy,posx);
  int cx,cy;getyx(this->window,cy,cx);
  posx+=cx;posy+=cy;
  vector<int> a;a.resize(2);
  a[0]=posx;a[1]=posy;
  return a;
};

Vector2D BaseWindow::GetGlobalCursorPos(int x,int y){
  int posx,posy;getbegyx(this->window,posy,posx);
  posx+=x;posy+=y;
    vector<int> a;a.resize(2);
  a[0]=posx;a[1]=posy;
  return a;
};

Vector2D BaseWindow::GetXY(){
  int x,y;getyx(this->window,y,x);
  Vector2D v;
  v.resize(2);
  v[0]=x;v[1]=y;
  return v;
};

Vector2D BaseWindow::GetMaxXY(){
  int x,y;getmaxyx(window,y,x);
  Vector2D v;
  v.resize(2);
  v[0]=x;v[1]=y;
  return v;
};

