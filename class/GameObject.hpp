#pragma once
#include "LogicComponent.hpp"

namespace scgb{
  template <class T>
  class GameObject:public LogicComponent{
    //LogicComponent which contains DrawingComponent.
  protected:
    std::unique_ptr<T> dcp;
  public:
    virtual void Draw(){dcp->Draw();};
    GameObject(T* dc){
      dcp=std::unique_ptr<T>(dc);
    }
    virtual ~GameObject(){}
  };
}
