#pragma once
#include "define.hpp"
#include <vector>
#include <algorithm>

namespace Invader{
  class Shield{
  private:
    const int width=4;
    const int height=5;
    const int hardness=2;
    
    std::vector<int> durability;
    int x;int y;
  public:
    Shield(int x,int y):durability(4*5,hardness){
      this->x=x;
      this->y=y;
    }
    
    void IsHit(Bullet* b){
      int cx=x-b->GetX();
      int cy=y-b->GetY();
      if(cx>=0 && cx<width && cy>=0 && cy<height){
	if(durability[cx*cy]>=0){
	  durability[cx*cy]--;
	  b->Hit();
	}
      }
    }
    
    scgb::Vector2D GetSize(){
      return scgb::Vector2D(x,y);
    }
  };
}
