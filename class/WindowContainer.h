#pragma once
#include "Drawable.h"
#include "Mediator.h"

namespace scgb{
  class WindowContainer:public Drawable,Handler{
  protected:
    std::map<int,scgb::pDrawable> drawentity;
    bool isHidden=false;
    EventMediator mediator=EventMediator(this);
  public:
    virtual void Draw();
    virtual void Refresh();
    virtual void Resize();
    virtual void Hide();
    virtual void Show();
    virtual void EventHandler(int i){};
    template <class T>
    WeakPtr<T> AddDrawable(int l,T* pd){
      if(drawentity.find(l)==drawentity.end()){
	std::shared_ptr<T> b;
	pd->SetMediator(&mediator);
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
    }
    ~WindowContainer(){
      drawentity.clear();
    }
  };
}
