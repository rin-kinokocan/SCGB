#pragma once
#include <algorithm>
#include <vector>
#include "Defender.hpp"
#include "DefenderBullet.hpp"
#include "EnemyBullet.hpp"
#include "Shield.hpp"
#include "Enemy.hpp"

namespace Invader{
  class GameModel{
  private:
    //constants
    const int enemyRow=11;
    const int enemyCol=5;
    const int maxX=16;
    const int minX=-5;
    const int enemyMarginX=2;
    const int enemyMarginY=1;
    int currentLevel=1;
    int counter=1000;
    int lives=3;
    bool direction=false;// false:right true:left 
    bool isGameOver=false;
    Defender defender;
    std::vector<EnemyBullet> enemyBullets;
    std::vector<DefenderBullet> defenderBullets;
    std::vector<Shield> shields;
    std::vector<Enemy> enemies;
  public:
    GameModel(){
      srand(91);
      for(int i=0;i<enemyCol;i++){
	for(int j=0;j<enemyRow;j++){
	  int type;
	  if(i<1)
	    type=Enemy::third;
	  else if(i<3)
	    type=Enemy::second;
	  else
	    type=Enemy::first;
	  enemies.push_back(Enemy(j*(Enemy::width+enemyMarginX),i*(Enemy::height+enemyMarginY),type));
	}
      }
    }
    
    int GetCurrentLevel(){
      return currentLevel;
    }
    std::vector<Enemy>& GetEnemies(){
      return enemies;
    }
    std::vector<Shield>& GetShields(){
      return shields;
    }
    std::vector<EnemyBullet>& GetEnemyBullets(){
      return enemyBullets;
    }
    std::vector<DefenderBullet>& GetDefenderBullets(){
      return defenderBullets;
    }
    Defender& GetDefender(){
      return defender;
    }
    
    void DefenderShot(){
      defender.Shot(defenderBullets);
    }
    void EnemieShot(){
      auto min=std::max_element(enemies.begin(),enemies.end(),
			   [](Enemy& e1,Enemy& e2){
			     return e1.GetY()<e2.GetY();
			   })->GetY();
      for(auto& e:enemies){
	if(e.GetY()==min){
	  auto d=e.GetX()-defender.GetX();
	  if(d<3 && d>-3){
	    e.Shot(enemyBullets);
	  }
	}
      }
    }
    void Update(int dt){
      counter-=dt;
      //Testing c++ algorithm functions... it looks bad.
      if(counter<=0){//Move Invaders
	//Test if there are any Invaders on edge
	//If someone on edge, turn the direction
	if(direction==false){
	  if(std::max_element(enemies.begin(),enemies.end(),
			 [](Enemy& e1,Enemy& e2){
			   return e1.GetX()<e2.GetX();
			 })->GetX()==maxX)
	    direction=true;
	}
	else{
	  if(std::min_element(enemies.begin(),enemies.end(),
			 [](Enemy& e1,Enemy& e2){
			   return e1.GetX()<e2.GetX();
			 })->GetX()==minX)
	    direction=false;
	}
	for(auto& e:enemies){
	  e.Move(direction);

	}
	counter=1000;
      }
      for(auto& eb:enemyBullets){
	eb.Update(dt);
      }
      for(auto& db:defenderBullets){
	db.Update(dt);
      }

      for(auto& s:shields){//Updates Sheilds
	for_each(enemyBullets.begin(),enemyBullets.end(),[&](EnemyBullet& eb){s.IsHit(&eb);});
	for_each(defenderBullets.begin(),defenderBullets.end(),[&](DefenderBullet& db){s.IsHit(&db);});
      }
      EnemieShot();//Invaders will shot some bullets.
      if(defender.IsHit(enemyBullets)){//Test if any enemy bullets hitting the defender
	lives--;
	if(lives<0){//if run out of lives, your game is over
	  isGameOver=true;
	}
      }
    }
  };
}
