#pragma once
#include "DrawingComponent.hpp"
#include "DCHandler.hpp"

namespace scgb{
  class WindowContainer:public DCHandler{
  protected:
    std::map<int,std::shared_ptr<DrawingComponent>> drawlist;
    std::map<int,Vector2D> positions;
  public:
    virtual void Draw(){
      for(auto i:drawlist){
	auto p=positions[i.first];
	i.second->Draw(x+p[0],y+p[1]);
      }
    }
  
    template <class T>
    std::shared_ptr<T> GetDC(int l){
      return std::static_pointer_cast<T>(drawlist[l]);
    }

    void AddDC(int l,DrawingComponent* d){
      AddDC(l,d,0,0);
    }
    void AddDC(int l,DrawingComponent* d,int x,int y){
      auto a=std::shared_ptr<DrawingComponent>(d);
      AddDC(l,a,x,y);
    }
    void AddDC(int l,std::shared_ptr<DrawingComponent> d){
      AddDC(l,d,0,0);
    }
    void AddDC(int l,std::shared_ptr<DrawingComponent> d,int x,int y){
      if(drawlist.find(l)==drawlist.end()){
	drawlist[l]=d;
	positions[l]=Vector2D(x,y);
      }
      else{
	std::string info="the layer ";
	info+=std::to_string(l);info+=" is already used";
	endwin();
	throw std::runtime_error(info);
      }
    }

    void DeleteDC(int l){
      auto a=drawlist.find(l);
      if(a!=drawlist.end()){
	drawlist.erase(a);
      }
    }

    WindowContainer(int x,int y):DCHandler(x,y){}
    virtual ~WindowContainer(){
      drawlist.clear();
    }
  };
}
