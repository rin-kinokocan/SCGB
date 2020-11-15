#pragma once
#include "scgb.hpp"
#include "Scene.hpp"
#include "MapData.hpp"
#include "MapBox.hpp"
#include "Parts.hpp"
using namespace scgb;
using namespace std;

class MainScene:public Scene{
protected:
  MapData map;
  std::wstring message=L"COIN GAINED:";
  int coin=0;
public:
  MainScene(int x=0,int y=0):map("assets/Map.txt",0,0){
    auto floor=Add(CompositeDrawingComponent());
    floor->Add(AABox("assets/Floor1.txt",x+3,y+14))->SetTransparency(true);
    floor->Add(AABox("assets/Floor2.txt",x+5,y+11))->SetTransparency(true);
    floor->Add(AABox("assets/FloorL.txt",x+3,y+11))->SetTransparency(true);
    floor->Add(AABox("assets/FloorR.txt",x+22,y+11))->SetTransparency(true);
    auto walls=Add(CompositeDrawingComponent());
    walls->Add(AABox("assets/LeftWallBetween.txt",x,y));//1
    walls->Add(AABox("assets/LeftWallBetween2.txt",x+3,y+3));//2
    walls->Add(AABox("assets/LeftWall1.txt",x,y));//3
    walls->Add(AABox("assets/LeftWall2.txt",x+2,y+1));//4
    walls->Add(AABox("assets/RightWallBetween.txt",x+27,y));//5
    walls->Add(AABox("assets/RightWallBetween2.txt",x+22,y+3));//6
    walls->Add(AABox("assets/RightWall1.txt",x+27,y));//7
    walls->Add(AABox("assets/RightWall2.txt",x+22,y+1));//8
    walls->Add(AABox("assets/FrontWall2.txt",x+7,y+3));//9
    walls->Add(AABox("assets/FrontWall1.txt",x+2,y));//10
    Add(Coin(x+11,y+4));
    Add(MapBox(map,x+50,y));
    Add(MessageWindow(message,0,1,15,50,10));
  }
  
  void Draw(){
    message=L"COIN GAINED:"+std::to_wstring(coin);
    int sight=map.GetSight(),count=0;
    int ground=map.GetGround();
    auto floor=GetComponent<CompositeDrawingComponent>(0);
    auto wall=GetComponent<CompositeDrawingComponent>(1);
    for(int i=0;i<10;i++){
      int num=1<<i;
      if(sight&num)
	wall->Draw(i);
    }
    for(int i=0;i<4;i++){
      int num=1<<i;
      if(ground&num && (sight&(1<<9))==0)
	floor->Draw(i);
    }
    if(map.GetCoin()){
      composite[2]->Draw();
    }
    for(int i=3;i<composite.size();i++){
      composite[i]->Draw();
    }
  }
  
  void Update(){
    auto pos=map.GetPosition();
    if(map.GetIcon(pos[0],pos[1])==1){
      map.SetIcon(pos[0],pos[1],0);
      coin++;
    }
  }
  
  void HandleInput(GameContext& gc,wint_t input,int code){
    switch(input){
    case KEY_UP:
      map.MoveForward();
      break;
    case KEY_RIGHT:
      map.TurnRight();
      break;
    case KEY_LEFT:
      map.TurnLeft();
      break;      
    case 'q':
      gc.EndGame();
    default:
      break;
    }  
  }
};
