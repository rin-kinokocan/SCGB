#pragma once
#include "Controller.hpp"
#include "GameModel.hpp"
#include "GameScene.hpp"

namespace Invader{
  class GameController:public Controller{
  private:
    GameModel gameModel;
  public:
    void Update(scgb::InputMap& im,int dt){
      Defender& d=gameModel.GetDefender();
      gameModel.Update(dt);
      if(im.GetBool(KEY_RIGHT)){
	d.RMove();
      }
      if(im.GetBool(KEY_LEFT)){
	d.LMove();
      }
    }
    GameController(Textures* textures,SceneManager* sm):
      Controller(textures,sm){
      sceneManager->Push(std::make_unique<GameScene>(*textures,gameModel));
    }
  };
}
