#pragma once
#include "Controller.hpp"
#include "ControllerManager.hpp"
#include "GameController.hpp"

namespace Invader{
  class TitleController:public Controller{
  private:
    ControllerManager* controllerManager;
  public:
    void Update(scgb::InputMap& im,int dt){
      if(im.GetBool(L's')){
	controllerManager->Push(std::make_unique<GameController>(textures,sceneManager));
      }
    }
    TitleController(Textures* t,SceneManager* sm,ControllerManager* cm)
      :Controller(t,sm){
      controllerManager=cm;
    }
  };
}
