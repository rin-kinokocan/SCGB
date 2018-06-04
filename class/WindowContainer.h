#pragma once
#include "define.h"
#include "BaseWindow.h"

namespace scgb{
  class WindowContainer:public Drawable{
  protected:
    std::map<int,scgb::pDrawable> drawentity;
    bool isHidden=false;
  public:
    virtual void Draw();
    virtual void Refresh();
    virtual void Resize();
    virtual void Hide();
    virtual void Show();
    template <class T>
    WeakDrawable<T> AddDrawable(int l,T* pd){
      if(drawentity.find(l)==drawentity.end()){
	std::shared_ptr<T> b;
	b.reset(pd);
	drawentity.insert(std::pair<int,pDrawable>(l,b));
	return WeakDrawable<T>(b);
      }
      else{
	std::string info="the layer ";
	info+=l;info+="is already used";
	endwin();
	throw new std::runtime_error(info);
      }
    }
  };
}
