#pragma once
#include "InputMap.hpp"
#include "Textures.hpp"
#include "SceneManager.hpp"

namespace Invader{
  class Controller{
  protected:
    SceneManager* sceneManager;
    Textures* textures;
  public:
    virtual void Update(scgb::InputMap& im,int dt){}
    Controller(Textures* t,SceneManager* sm){
      textures=t;
      sceneManager=sm;
    }
  };
}
