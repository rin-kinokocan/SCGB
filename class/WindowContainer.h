#pragma once
#include "Drawable.h"

namespace scgb{
  class WindowContainer:public Drawable{
  protected:
    int width,height,x,y;
    std::map<int,scgb::pDrawable> drawentity;
    bool isHidden=false;
  public:
    virtual void Draw();
    virtual void Refresh();
    virtual void OnResize();
    virtual void DrawOnScreen();
    virtual void Hide();
    virtual void Show();
    virtual Vector2D GetMaxXY();
    virtual cChar GetWholeScreen(int x,int y);
    virtual void AddWholeScreen(int x,int y,cChar c);
    
    template <class T>
    WeakPtr<T> AddDrawable(int l,T* pd){
      if(drawentity.find(l)==drawentity.end()){
	std::shared_ptr<T> b;
	pd->SetParent(this);
	b.reset(pd);
	drawentity.insert(std::pair<int,pDrawable>(l,b));
	return WeakPtr<T>(b);
      }
      else{
	std::string info="the layer ";
	info+=l;info+="is already used";
	endwin();
	throw new std::runtime_error(info);
      }
    };
    virtual void DeleteDrawable(int l);
    
    WindowContainer(int x,int y,int width,int height){
      auto a=Util::GetMaxScrXY();
      if(x<=0)
	this->x=a[0];
      else
	this->x=x;
      if(y<=0)
	this->y=a[1];
      else
	this->y=y;
      this->width=width;
      this->height=height;
    };
    
    virtual ~WindowContainer(){
      drawentity.clear();
    };
  };
}
