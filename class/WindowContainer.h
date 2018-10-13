#pragma once
#include "DrawingComponent.hpp"

namespace scgb{
  class WindowContainer:public DrawingComponent{
  protected:
    std::map<int,std::shared_ptr<DrawingComponent>> drawlist;
  public:
    virtual void Draw();
    virtual void Hide();
    virtual void Show();
    
    template <class T>
    WeakPtr<T> GetDrawable(int l){
      auto a=std::static_pointer_cast<T>(drawlist[l]);
      return WeakPtr<T>(a);
    }
    
    template <class T>
    WeakPtr<T> AddDrawable(int l,T* d){
      if(drawlist.find(l)==drawlist.end()){
	//I know it's a bad idea. I know it.
	std::shared_ptr<DrawingComponent> b(d);
	drawlist[l]=b;
	return WeakPtr<T>(std::static_pointer_cast<T>(b));
      }
      else{
	std::string info="the layer ";
	info+=std::to_string(l);info+="is already used";
	endwin();
	throw std::runtime_error(info);
      }
    };
    virtual void DeleteDrawable(int l);

    WindowContainer(double,double,int,int);
    virtual ~WindowContainer(){
      drawlist.clear();
    };
  };
}
