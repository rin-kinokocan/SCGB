#pragma once
#include "scgb.hpp"
#include "Scene.hpp"
#include "MapData.hpp"
#include "Map3D.hpp"
#include "MapBox.hpp"
#include "Parts.hpp"
#include "Camera.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace scgb;
using namespace std;

class TestScene:public Scene{
protected:
  MapData map;
  float angle=90;
  Camera camera;
  std::wstring message=L"COIN GAINED:";
  int coin=0;
  int width=70;
  int height=25;
public:
  TestScene(int x=0,int y=0):map("assets/Map.txt",0,0),camera(glm::vec3(3.0f,1.0f,3.0f)){
    Add(Map3D(map,x+1,y+1,32,18));
    Add(Rectangle(0,0,0,34,20));
    Add(MapBox(map,x+50,y));
    Add(MessageWindow(message,0,1,22,50,10));
  }
  
  void Draw(){
    camera.SetYaw(angle);
    auto map=GetComponent<Map3D>(0);
    for(auto c:composite)
      c->Draw();
    map->Draw(camera);
    message=L"This is a demonstration of SCGB functionality.\n これはSCGBのデモ画面です。";
  }
  void Update(){
    auto pos=map.GetPosition();
    if(map.GetIcon(pos[0],pos[1])==1){
      map.SetIcon(pos[0],pos[1],0);
      coin++;
    }
    if(isMoving){
      int cellsizex=GetComponent<Map3D>(0)->GetCellSize();
      distance+=velocity;
      camera.Move(velocity);
      if(abs(distance)>=cellsizex){
	camera.Move(-velocity/abs(velocity)*(abs(distance)-cellsizex));// adjust position
	distance=0;
	isMoving=false;
      }
    }
    if(isTurning){
      float maxangle=90.0f;
      turnedangle+=angvelocity;
      angle+=angvelocity;
      if(abs(turnedangle)>=maxangle){
	angle+=-angvelocity/abs(angvelocity)*(abs(turnedangle)-maxangle);
	turnedangle=0;
	isTurning=false;
      }
    }
  }
  bool isMoving=false;
  bool isTurning=false;
  float velocity=0;
  float angvelocity=0;
  float distance=0;
  float turnedangle=0;
  void HandleInput(GameContext& gc,wint_t input,int code){
    if(isMoving || isTurning){
      return;
    }
    auto position=map.GetPosition();
    GetComponent<MapBox>(2)->SetFlag(position[0],position[1]);
    switch(input){
    case KEY_UP:
      if(map.MoveForward()){
	isMoving=true;
	velocity=-2.0f;
      }
      break;
    case KEY_RIGHT:
      map.TurnRight();
      isTurning=true;
      angvelocity=24.0f;
      break;
    case KEY_LEFT:
      map.TurnLeft();
      isTurning=true;
      angvelocity=-24.0f;
      break;
    case KEY_DOWN:
      if(map.MoveBackward()){
	isMoving=true;
	velocity=2.0f;
      }
      break;
    case 'q':
      gc.EndGame();
      break;
    default:
      break;
    }  
  }
};
