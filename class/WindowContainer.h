#pragma once
#include "DrawingComponent.hpp"

namespace scgb{
  class WindowContainer:public DrawingComponent{
  protected:
    std::map<int,std::shared_ptr<DrawingComponent>> drawlist;
    int width,height;
  public:
    virtual void Draw(int x,int y);
    
    template <class T>
    std::shared_ptr<T> GetDrawable(int l){
      return std::static_pointer_cast<T>(drawlist[l]);
    }
    
    void AddDrawable(int l,std::shared_ptr<DrawingComponent> d){
      if(drawlist.find(l)==drawlist.end()){
	drawlist[l]=d;
      }
      else{
	std::string info="the layer ";
	info+=std::to_string(l);info+="is already used";
	endwin();
	throw std::runtime_error(info);
      }
    }
    
    void AddDrawable(int l,DrawingComponent* d){
      auto a=std::shared_ptr<DrawingComponent>(d);
      this->AddDrawable(l,a);
    }
    
    virtual void DeleteDrawable(int l);

    WindowContainer(int w,int h):DrawingComponent(){}
    
    virtual ~WindowContainer(){
      drawlist.clear();
    }
  };
}
