#pragma once
#include "BaseWindow.h"

namespace scgb{
  class PlainWindow:public BaseWindow{
    //just a rectangle of a given color.
  public:
    virtual void Draw();
    bool isBox;
    chtype ColorPair;
    virtual void WindowSetting();
    PlainWindow(int,int,int,int,SizeData*,chtype,bool);
  };
  
  class PWBuilder:public DrawableBuilder{
  protected:
    bool isBox=false;
    chtype color=0;
  public:
    Drawable* GetResult(){
      return new PlainWindow(x,y,w,h,psd,color,isBox);
    }
    PWBuilder(double x,double y,int w,int h)
      :DrawableBuilder(x,y,w,h){};
    PWBuilder& SetBox(bool i){isBox=i;return *this;};
    PWBuilder& SetColor(chtype c){color=c;return *this;};
    virtual ~PWBuilder(){};
  };
}
