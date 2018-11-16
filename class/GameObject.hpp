#pragma once
#include "LogicComponent.hpp"

namespace scgb{
  class GameObject:public LogicComponent{
    //LogicComponent which contains DrawingComponent.
  protected:
    std::shared_ptr<DrawingComponent> dcp;
    double x,y;//upleft coodinates
    bool isHidden=false;
  public:
    virtual void Draw(){dcp->Draw(x,y);};
    virtual void Hide(){isHidden=true;}
    virtual void Show(){isHidden=false;}
    void AttachDrawingComponent(DrawingComponent* dc){
      dcp=std::shared_ptr<DrawingComponent>(dc);
    }
    void AttachDrawingComponent(std::shared_ptr<DrawingComponent> dc){
      dcp=dc;
    }
    template <class T>
    std::shared_ptr<T> GetDrawingComponent(){
      return std::dynamic_pointer_cast<T>(dcp);
    }
    GameObject(int x,int y,DrawingComponent* dc):GameObject(x,y){
      this->AttachDrawingComponent(dc);
    }
    GameObject(double x,double y){
      this->x=x;this->y=y;
    }
    virtual ~GameObject(){}
  };
}
