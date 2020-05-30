#pragma once
#include <vector>
#include "DefenderBullet.hpp"
#include "EnemyBullet.hpp"

namespace Invader{
  class Defender{
    int x=40;
    const int y=30;
  public:
    void Shot(std::vector<DefenderBullet>& v){
    }
    scgb::Vector2D GetPosition(){
      return scgb::Vector2D(x,y);
    }
    int GetX(){
      return x;
    }
    void RMove(){
      x+=3;
    }
    void LMove(){
      x-=3;
    }
    bool IsHit(std::vector<EnemyBullet>& v){
      return true;
    }
  };
}
