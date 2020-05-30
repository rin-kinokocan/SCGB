#pragma once

namespace Invader{
  class Bullet{
  private:
    int x;
    int y;
    bool isHit=false;
  public:
    Bullet(int x,int y){
      this->x=x;
      this->y=y;
    }
    int GetX(){
      return x;
    }
    int GetY(){
      return y;
    }
    bool IsHit(){
      return isHit;
    }
    void Hit(){
      isHit=true;
    }
    virtual void Update(int dt)=0;
  };
}
