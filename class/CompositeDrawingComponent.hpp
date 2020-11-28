#pragma once
#include "DrawingComponent.hpp"
#include <memory>

namespace scgb{
  class CompositeDrawingComponent:public DrawingComponent{
  protected:
    std::vector<std::shared_ptr<DrawingComponent>> composite;
    template <class T> std::shared_ptr<T> GetComponent(int i){
      if(i<0 || i>composite.size()){
	endwin();
	throw(std::runtime_error("Out of boundary"));
      }
      return std::dynamic_pointer_cast<T>(composite[i]);
    }
  public:
    CompositeDrawingComponent(int x=0,int y=0,int w=0,int h=0):DrawingComponent(x,y,w,h){}
    template <class T> std::shared_ptr<T> Add(T&& dc,int i){
      if(i>=composite.size()){
	composite.resize(i+1);
      }
      composite[i]=std::make_shared<T>(std::move(dc));
      return std::dynamic_pointer_cast<T>(composite[i]);
    }
    template <class T> std::shared_ptr<T> Add(T&& dc){
      composite.push_back(std::make_shared<T>(std::move(dc)));
      return std::dynamic_pointer_cast<T>(composite.back());
    }
    
    void Draw(){
      for(auto d:composite){
	d->Draw();
      }
    }
    void Draw(int i){
      if(i<0 || i>composite.size()){
	endwin();
	throw(std::runtime_error("Out of boundary"));
      }
      composite[i]->Draw();
    }

    void SetTransparency(bool t){
      for(auto d:composite){
	d->SetTransparency(t);
      }
    }    
    void Move(int dx,int dy){
      this->x+=dx;this->y+=dy;
      for(auto d:composite){
	d->Move(dx,dy);
      }
    }
    void MoveTo(int x,int y){
      this->x=x;this->y=y;
      for(auto d:composite){
	d->MoveTo(x,y);
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
  };
}
