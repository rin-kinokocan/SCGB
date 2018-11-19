#pragma once
#include "DCHandler.hpp"

namespace scgb{
  class WindowContainer:public DCHandler{
  protected:
    std::map<int,std::shared_ptr<DrawingComponent>> drawlist;
  public:
    virtual void Draw(){
      for(auto i:drawlist){
	i.second->Draw(x,y);
      }
    }
  
    template <class T>
    std::shared_ptr<T> GetDC(int l){
      return std::static_pointer_cast<T>(drawlist[l]);
    }
    
    void AddDC(int l,std::shared_ptr<DrawingComponent> d){
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
    
    void AddDC(int l,DrawingComponent* d){
      auto a=std::shared_ptr<DrawingComponent>(d);
      this->AddDC(l,a);
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
