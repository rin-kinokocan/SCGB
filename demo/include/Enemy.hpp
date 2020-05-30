#pragma once
#include <define.hpp>
#include <vector>
#include "EnemyBullet.hpp"

namespace Invader{
  class Enemy{
  private:
    int type;
    int x,y;
  public:
    scgb::Vector2D GetPosition(){
      return scgb::Vector2D(x,y);
    }
    int GetX(){
      return x;
    }
    int GetY(){
      return y;
    }
    int GetType(){
      return type;
    }
    void Shot(std::vector<EnemyBullet> eb){
    }
    void Move(int direction){}
    Enemy(int x,int y,int type){
      this->x=x;
      this->y=y;
      this->type=type;
    }
    const static int first=0;
    const static int second=1;
    const static int third=2;
    const static int height=3;
    const static int width=8;
  };
}
