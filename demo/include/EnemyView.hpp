#pragma once
#include <vector>
#include "View.hpp"
#include "Textures.hpp"
#include "Enemy.hpp"

namespace Invader{
  class EnemyView:public View{
  private:
    std::vector<Enemy>* enemies;
    scgb::AAtext invader1;
    scgb::AAtext invader2;
    scgb::AAtext invader3;
    const int width=10;
    const int height=5;
    const int xoffset=15;
    const int yoffset=7;
  public:
    void Draw(){
      for(auto &e:(*enemies)){
	auto ep=e.GetPosition();
	ep[0]+=xoffset;
	ep[1]+=yoffset;
	switch(e.GetType()){
	case Enemy::first:
	  invader1.SetOrigin(ep);
	  invader1.Draw();
	  break;
	case Enemy::second:
	  invader2.SetOrigin(ep);
	  invader2.Draw();
	  break;
	case Enemy::third:
	  invader3.SetOrigin(ep);
	  invader3.Draw();
	  break;
	default:
	  break;
	}
      }
    }
    
    EnemyView(Textures& textures,std::vector<Enemy>& e){
      invader1.SetAAfile(textures["Invader1"]);
      invader2.SetAAfile(textures["Invader2"]);
      invader3.SetAAfile(textures["Invader3"]);
      enemies=&e;
    }
  };
}
