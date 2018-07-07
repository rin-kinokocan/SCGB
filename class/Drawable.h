#pragma once
#include "define.h"
#include "SizeData.h"
#include "Movable.h"

namespace scgb{
  class Drawable:public Movable{
  protected:
    double x,y;
    int width,height;
    SizeData* psd=nullptr;
  public:
    virtual void Draw(){};
    virtual void Refresh(){};
    virtual void OnResize(){};
    virtual void Hide(){};
    virtual void Show(){};
    Drawable(double px,double py,int w,int h,SizeData* ppsd){
      x=px;y=py;width=w;height=h;psd=ppsd;
    };
    Drawable(SizeData* ppsd){psd=ppsd;};
    virtual ~Drawable(){};
  };
  
  class DrawableBuilder{
  protected:
    int x,y,w,h;
    SizeData* psd=nullptr;
  public:
    virtual Drawable* GetResult()=0;
    void SetPSD(SizeData* sd){psd=sd;};
    DrawableBuilder(int px,int py,int pw,int ph){
      x=px;y=py;w=pw;h=ph;
    };
    virtual ~DrawableBuilder(){};
  };

}

