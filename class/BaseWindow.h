#pragma once
#include "Drawable.h"

namespace scgb{
  class BaseWindow :public Drawable{
  private:
    int curx=0;
    int cury=0;
  protected:
    bool isHidden=false;
    void InitDraw();
    bool MoveAfterDraw(int w);
    bool AddChar(cChar c);//for file reading things,I guess?
    bool DrawPolicy(int w);
    virtual void WindowSetting(){};
  public:
    virtual void OnResize();
    virtual void Hide();
    virtual void Show();
    //Movable implementations
    virtual void rmove();
    virtual void lmove();
    virtual void umove();
    virtual void dmove();
    //Drawing methods
    void MoveCursor(int x,int y);
    void AddChar(cChar c,int x,int y);//for normal use.
    void AddStr(std::vector<cChar>,int x,int y);//to add string.
    
    BaseWindow(int,int,int,int,SizeData*);
    virtual ~BaseWindow(){};
  };
  
  class BWBuilder:public DrawableBuilder{
  public:
    virtual Drawable* GetResult(){
      return new BaseWindow(x,y,w,h,psd);
    };
    BWBuilder(double x,double y,double w,int h)
      :DrawableBuilder(x,y,w,h){};
    virtual ~BWBuilder(){};
  };
}
