#pragma once
#include "scgb.hpp"
#include "MapData.hpp"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL 1
#include <glm/gtx/string_cast.hpp>
using namespace scgb;
using namespace std;

class Map3D:public DrawingComponent{
protected:
  vector<glm::vec3> vertices;
  vector<glm::vec4> faces;
  int AddVertex(glm::vec3 v){
    int pos=-1;
    for(int i=0;i<vertices.size();i++){
      if(glm::length(v-vertices[i])<0.01f){
	pos=i;
	break;
      }
    }
    if(pos==-1){
      vertices.push_back(v);
      pos=std::distance(vertices.begin(),vertices.end());
    }
    return pos;
  }
  void AddFace(int a,int b,int c,int d){
    faces.push_back(glm::vec4(a,b,c,d));
  }
  void AddCol(int i,int j){
    auto a=AddVertex(glm::vec3(i,0,j));
    auto b=AddVertex(glm::vec3(i,1,j));
    auto c=AddVertex(glm::vec3(i,0,j+1));
    auto d=AddVertex(glm::vec3(i,1,j+1));
    AddFace(a,b,c,d);
  }
  void AddRow(int i,int j){
    auto a=AddVertex(glm::vec3(i,0,j));
    auto b=AddVertex(glm::vec3(i,1,j));
    auto c=AddVertex(glm::vec3(i+1,0,j));
    auto d=AddVertex(glm::vec3(i+1,1,j));
    AddFace(a,b,c,d);
  }
  public:
  const vector<glm::vec3>& GetVertices(){
    return vertices;
  }
  const vector<glm::vec4>& GetFaces(){
    return faces;
  }
  void Draw(){};
  Map3D(MapData &md,int x,int y,int w=32,int h=18):DrawingComponent(x,y,w,h){
    auto col=md.GetColWalls();
    auto row=md.GetRowWalls();
    auto size=md.GetSize();
    for(int i=0;i<size[0]+1;i++){
      for(int j=0;j<size[1];j++){
	if(col[i*size[1]+j]==1){
	  AddCol(i,j);
	}
      }
    }
    for(int i=0;i<size[0];i++){
      for(int j=0;j<size[1]+1;j++){
	if(row[i*(size[1]+1)+j]==1){
	  AddRow(i,j);
	}
      }
    }
  }
};
