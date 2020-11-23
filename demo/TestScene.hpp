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
  float angle;
  Camera camera;
  std::wstring message=L"COIN GAINED:";
  int coin=0;
  int width=70;
  int height=25;
public:
  TestScene(int x=0,int y=0):map("assets/Map.txt",0,0),camera(glm::vec3(0,0.5,-1.0f)){
    Add(Map3D(map,x,y));
    Add(Coin(x+11,y+4));
    Add(MapBox(map,x+50,y));
    Add(MessageWindow(message,0,1,15,50,10));
  }
  
  void Draw(){
    // glm::mat4 translate=glm::translate(glm::mat4(1.0f),position);
    // glm::mat4 rotate=glm::rotate(translate,glm::radians(angle),glm::vec3(0.0f,1.0f,0.0f));
    vector<glm::vec3> vertices;
    vertices.push_back(glm::vec3(-1,0,0));
    vertices.push_back(glm::vec3(1,0,0));
    vertices.push_back(glm::vec3(0,1,0));
    camera.SetYaw(angle);
    //auto vertices=map3d.GetVertices();
    vector<glm::vec3> calculated;
    auto view=camera.GetViewMat();
    int count=0;
    static float angle=0;
    angle+=0.1;
    auto projection=glm::perspective(glm::radians(45.0f), (float)width/height, 0.1f, 400.0f);
    auto rotate=glm::rotate(glm::mat4(1.0f),angle,glm::vec3(0,1,0));
    for(glm::vec3 ver:vertices){
      //auto v=projection*rotate*glm::vec4(ver,1.0f);
      auto v=projection*view*rotate*glm::vec4(ver,1.0f);
      int x=width*(v[0]/(v[3]+0.001)+1)/2;
      int y=height*(-v[1]/(v[3]+0.001)+1)/2;
      if(abs(v[0]/(v[3]+0.001))<1.0f && abs(v[1]/(v[3]+0.001))<1.0f && v[3]>0){	
	if(y>=0 && x>=0){
	  move(y,x);
	  addch('@');
	}
	calculated.push_back(glm::vec3(x,y,1.0f));
      }
      else if(v[3]<0)
	calculated.push_back(glm::vec3(x,y,-1.0f));
      else
	calculated.push_back(glm::vec3(x,y,1.0f));
      move(count,0);
      addstr(glm::to_string(calculated[count]).c_str());
      count++;
    }
    if(calculated[0].z>0 && calculated[1].z>0)
      DrawEdge(calculated[0],calculated[1]);
    if(calculated[1].z>0 && calculated[2].z>0)
      DrawEdge(calculated[1],calculated[2]);
    if(calculated[0].z>0 && calculated[2].z>0)
      DrawEdge(calculated[0],calculated[2]);

    message=L"COIN GAINED:"+std::to_wstring(coin);
  }
  void DrawEdge(glm::vec2 from,glm::vec2 to){
    int x0=from.x,y0=from.y;
    auto edgevec=to-from;
    int dx1=0,dy1=0,dx2=0,dy2=0;
    int longer=abs(edgevec.x),shorter=abs(edgevec.y);
    if(edgevec.x<0) dx1=-1;else if(edgevec.x>0) dx1=1;// going left or right when updated
    if(edgevec.y<0) dy1=-1;else if(edgevec.y>0) dy1=1;// going up or down when updated
    if(edgevec.x<0) dx2=-1;else if(edgevec.x>0) dx2=1;// going left or right when not updated
    if(longer<shorter){//move length width
      longer=abs(edgevec.y);
      shorter=abs(edgevec.x);
      dx2=0;
      if(edgevec.y<0) dy2=-1;else if(edgevec.y>0) dy2=1;// going up or down when not updated
    }
    int error=longer/2;
    for(int i=0;i<longer;i++){
      move(y0,x0);
      error+=shorter;
      if(error>longer){
	error-=longer;
	x0+=dx1;y0+=dy1;
	if(y0>=0 && x0>=0 && y0<=height && x0<=width){
	  if(edgevec.y<0)
	    addch('\'');
	  else
	    addch(',');
	}
      }
      else{
	x0+=dx2;y0+=dy2;
	if(y0>=0 && x0>=0 && y0<=height && x0<=width)
	  addch('.');
      }	
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
      camera.Move(0.5);
      break;
    case KEY_RIGHT:
      angle+=5.0f;
      break;
    case KEY_LEFT:
      angle-=5.0f;
      break;
    case KEY_DOWN:
      camera.Move(-0.5);
      break;
    case 'q':
      gc.EndGame();
    default:
      break;
    }  
  }
};
