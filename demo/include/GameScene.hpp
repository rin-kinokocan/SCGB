#pragma once
#include "Scene.hpp"
#include "EnemyView.hpp"
#include "GameModel.hpp"
#include "Textures.hpp"
#include "DefenderView.hpp"

namespace Invader{
  class GameScene:public Scene{
  private:
    GameModel* gameModel;
    EnemyView ev;
    DefenderView dv;
    scgb::AAtext ufo;
    scgb::Rectangle base;
    
  public:
    void Draw(){
     //  auto u=gameModel->GetUFO();
     //  if(u.IsAlive()){
     // 	ufo.SetOrigin(u.GetPosition());
     // 	ufo.Draw();
     // }
      base.Draw();
      ev.Draw();
      dv.Draw();
    }
    
    GameScene(Textures& textures,GameModel& gm)
      :ev(textures,gm.GetEnemies()),dv(textures,gm.GetDefender()){
      gameModel=&gm;
      base.SetSize(200,50);
      base.SetBorder(true);
      ufo.SetAAfile(textures["UFO"]);
   }
  };
}
