#pragma once
#include "DCHandler.hpp"

namespace scgb{
  class SingleHandler:public DCHandler{
  protected:
    std::shared_ptr<DrawingComponent> dcp;
  public:
    virtual void Draw(){dcp->Draw(x,y);};
    void AttachDC(DrawingComponent* dc){
      dcp=std::shared_ptr<DrawingComponent>(dc);
    }
    void AttachDC(std::shared_ptr<DrawingComponent> dc){
      dcp=dc;
    }
    template <class T>
    std::shared_ptr<T> GetDC(){
      return std::dynamic_pointer_cast<T>(dcp);
    }
    SingleHandler(int x,int y,DrawingComponent* dc):SingleHandler(x,y){
      this->AttachDC(dc);
    }
    SingleHandler(double x,double y):DCHandler(x,y){}
    virtual ~SingleHandler(){}
  };
}
