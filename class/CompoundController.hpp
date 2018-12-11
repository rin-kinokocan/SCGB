#pragma once
#include "BaseController.hpp"
#include <vector>
#include <memory>

namespace scgb{
  class CompoundController:public BaseController{
  protected:
    std::vector<std::unique_ptr<BaseController>> controllers;
  public:
    virtual void Draw(){
      for(auto c:controllers){
	c->Draw();
      }
    }
    void Append(BaseController a){
      // controllers.append(std::make_unique<BaseController>());
    }
    void Insert(){
    }
  };
}
