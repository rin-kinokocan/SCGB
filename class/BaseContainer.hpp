#include "define.hpp"
#include "ContainerInterface.hpp"
#include "LogicComponent.hpp"
#include "DrawingComponent.hpp"

namespace scgb{
  class BaseContainer:public ContainerInterface{
    // Work as a controller.
    // Most of your work will be to extend this class.
  protected:
    std::map<int,std::shared_ptr<LogicComponent>> lcs; // Models
    std::map<int,std::shared_ptr<DrawingComponent>> dcs; // Views

    void AddLC(int l,LogicComponent lc){
      lcs[l]=std::make_shared<LogicComponent>(std::move(lc));
    }
    void AddLC(int l,LogicComponent* lc){
      lcs[l]=std::shared_ptr<LogicComponent>(lc);
    }
    void AddLC(int l,std::shared_ptr<LogicComponent> lc){
      lcs[l]=lc;
    }
    void AddDC(int l,DrawingComponent dc){
      dcs[l]=std::make_shared<DrawingComponent>(std::move(dc));
    }
    void AddDC(int l,DrawingComponent* dc){
      dcs[l]=std::shared_ptr<LogicComponent>(dc);
    }
    void AddDC(int l,std::shared_ptr<DrawingComponent> dc){
      dcs[l]=dc;
    }
  public:
    void Draw(){
      for(auto dc:dcs){
	dc.second->Draw();
      }
    }
    
    void Exec(InputMap im){
      for(auto a:lcs){
	a.second->Exec();
      }
    }
  };
}
