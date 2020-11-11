#pragma once
#include "DrawingComponent.hpp"
#include <memory>

namespace scgb{
  class CompositeDrawingComponent:public DrawingComponent{
  protected:
    std::vector<std::shared_ptr<DrawingComponent>> composite;
  public:
    CompositeDrawingComponent(CompositeDrawingComponent&& c):composite(std::move(c.composite)){}
    CompositeDrawingComponent(int x=0,int y=0,int w=0,int h=0):DrawingComponent(x,y,w,h){}
    template <class T> std::shared_ptr<DrawingComponent> Add(T&& dc,int i){
      if(i>=composite.size()){
	composite.resize(i+1);
      }
      composite[i]=std::make_shared<T>(std::move(dc));
      return composite[i];
    }
    template <class T> std::shared_ptr<DrawingComponent> Add(T&& dc){
      composite.push_back(std::make_shared<T>(std::move(dc)));
      return composite.back();
    }
    void Draw(){
      for(auto d:composite){
	d->Draw();
      }
    }
    void Move(int dx,int dy){
      for(auto d:composite){
	d->Move(dx,dy);
      }
    }
    void Remove(int i){
      if(i>=composite.size()){
	return;
      }
      else{
	composite.erase(composite.begin()+i);
      }	
    }
    void Remove(){
      composite.erase(composite.end());
    }
    std::shared_ptr<DrawingComponent>& operator[](int i){
      if(i<0 || i>=composite.size())
	std::runtime_error("Out of Range");
      return composite[i];
    }
  };
}
