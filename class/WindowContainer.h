#pragma once
#include "define.h"
#include "BaseWindow.h"

namespace scgb{
  class WindowContainer:public Drawable{
  protected:
    DrawList drawentity;
  public:
    void Refresh();
    void Resize();
    template <class T>
    std::shared_ptr<T> AddDrawable(Layer l,T* pd){
      if(drawentity.find(l)==drawentity.end()){
	std::shared_ptr<T> b;
	b.reset(pd);
	drawentity.insert(std::pair<Layer,pBaseWindow>(l,b));
	return b;
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
