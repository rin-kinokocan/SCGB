#pragma once
#include "SceneManager.hpp"
#include "GameModel.hpp"
#include "Controller.hpp"
#include <memory>

namespace Invader{
  class ControllerManager{
  private:
    std::vector<std::unique_ptr<Controller>> controllers;
  public:
    void Push(std::unique_ptr<Controller> c){
      controllers.push_back(std::move(c));
    }
    void Pop(){
      controllers.pop_back();
    }
    void Update(scgb::InputMap& im,int dt){
      controllers.back()->Update(im,dt);
    }
  };
}
