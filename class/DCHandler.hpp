#pragma once
#include "LogicComponent.hpp"
#include "Movable.hpp"

namespace scgb{
  class DCHandler:public LogicComponent,Movable{
  protected:
    bool isHidden=false;
    double x,y;//upleft coodinates
  public:
    virtual void Draw()=0;
    virtual void Hide(){isHidden=true;}
    virtual void Show(){isHidden=false;}
    virtual void AttachDC(DrawingComponent* dc){};
    virtual void AttachDC(std::shared_ptr<DrawingComponent> dc){};
    virtual void Move(Direction dir){
      switch(dir){
      case Right:
	this->x+=1;
	break;
      case Left:
	this->x-=1;
	break;
      case Up:
	this->y-=1;
	break;
      case Down:
	this->y+=1;
	break;
      }
    };
    DCHandler(double x,double y){
      this->x=x;this->y=y;
    }
    virtual ~DCHandler(){}
  };
}
