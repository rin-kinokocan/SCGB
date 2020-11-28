#pragma once
#include "scgb.hpp"
#include "MapData.hpp"
#include "Camera.hpp"
#include "Parts.hpp"
#include <vector>
#include <numeric>
#include <limits>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL 1
#include <glm/gtx/string_cast.hpp>
using namespace scgb;
using namespace std;

class Map3D:public CompositeDrawingComponent{
public:
  int GetCellSize(){
    return cellsizex;
  }
protected:
  vector<glm::vec3> vertices;
  vector<glm::vec4> faces;
  vector<float> zbuffer;
  vector<int> entities;
  float fov=45.0f;
  int cellsizex=6;
  int cellsizey=3;
  int renderdistance=20;
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
      pos=vertices.size()-1;
    }
    return pos;
  }
  void AddFace(int a,int b,int c,int d){
    faces.push_back(glm::vec4(a,b,c,d));
  }
  void AddCol(int i,int j){
    auto a=AddVertex(glm::vec3(cellsizex*i,cellsizey,cellsizex*(j+1)));
    auto b=AddVertex(glm::vec3(cellsizex*i,cellsizey,cellsizex*j));
    auto c=AddVertex(glm::vec3(cellsizex*i,0,cellsizex*j));
    auto d=AddVertex(glm::vec3(cellsizex*i,0,cellsizex*(j+1)));
    AddFace(a,b,c,d);
  }
  void AddRow(int i,int j){
    auto a=AddVertex(glm::vec3(cellsizex*i,cellsizey,cellsizex*j));
    auto b=AddVertex(glm::vec3(cellsizex*(i+1),cellsizey,cellsizex*j));
    auto c=AddVertex(glm::vec3(cellsizex*(i+1),0,cellsizex*j));
    auto d=AddVertex(glm::vec3(cellsizex*i,0,cellsizex*j));
    AddFace(a,b,c,d);
  }
  void AddEntity(int x,int y){
    entities.push_back(AddVertex(glm::vec3(cellsizex*(x+0.5),cellsizey*0.2,cellsizex*(y+0.5))));
  }
public:
  const vector<glm::vec3>& GetVertices(){
    return vertices;
  }
  const vector<glm::vec4>& GetFaces(){
    return faces;
  }
  
  Map3D(MapData &md,int x,int y,int w=32,int h=18):CompositeDrawingComponent(x,y,w,h){
    zbuffer=vector<float>(w*h,std::numeric_limits<float>::infinity());
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
    for(int i=0;i<size[0];i++){
      for(int j=0;j<size[1];j++){
    	if(md.GetIcon(i,j)>0){
    	  AddEntity(i,j);
    	}
      }
    }
  }
    
  void Draw(){
    MoveCursor(0,0);
    AddStr("Pass me a camera!",0);
  }
  void Draw(Camera& camera){
    std::fill(zbuffer.begin(), zbuffer.end(), std::numeric_limits<float>::infinity());
    vector<glm::vec4> normalized;
    auto view=camera.GetViewMat();
    auto position=camera.GetPosition();
    auto projection=glm::perspective(glm::radians(fov), (float)width/height, 0.1f, 400.0f);
    
    for(glm::vec3 ver:vertices){
      auto v=projection*view*glm::vec4(ver,1.0f);
      normalized.push_back(v);
    }

    for(auto face :faces){
      // when top left side of a face is too far away, the face is not rendered.
      if(length(position-vertices[(int)face.x])>renderdistance)
	continue;
      std::vector<glm::vec4> vers;
      std::vector<glm::vec3> onscreen;
      vers.push_back(normalized[(int)face.x]);
      vers.push_back(normalized[(int)face.y]);
      vers.push_back(normalized[(int)face.z]);
      vers.push_back(normalized[(int)face.w]);

      for(auto ver:vers){	
	int del=0.0001;
	int x=width*(ver.x/abs(ver.w+del)+1)/2,y=height*(-ver.y/abs(ver.w+del)+1)/2;
	float z=ver.z/abs(ver.w+del);
	onscreen.push_back(glm::vec3(x,y,z));
      }
    
      int minx=max(0.0f,min(onscreen[0].x,min(onscreen[1].x,min(onscreen[2].x,onscreen[3].x))));
      int maxx=min((float)width,max(onscreen[0].x,max(onscreen[1].x,max(onscreen[2].x,onscreen[3].x))));
      int miny=max(0.0f,min(onscreen[0].y,min(onscreen[1].y,min(onscreen[2].y,onscreen[3].y))));
      int maxy=min((float)height,max(onscreen[0].y,max(onscreen[1].y,max(onscreen[2].y,onscreen[3].y))));
      for(int j=miny;j<=maxy;j++){
	int count=0;
	for(int i=minx;i<=maxx;i++){
      	  if(IsInside(i,j,onscreen[0],onscreen[1],onscreen[2],onscreen[3])){
      	    float z=CalcZ(i,j,onscreen[0],onscreen[1],onscreen[2],onscreen[3]);
	    if(i<0 || i>=width || j<0 || j>=height)
	      continue;
      	    if(z<0.0f || z>zbuffer[i+j*width])
	      continue;
	    else
      	      zbuffer[i+j*width]=z;
	    if((i==minx) && (j==miny))
	      continue;
	    MoveCursor(i,j);
	    bool isdiagonal=false;
	    glm::vec2 first,second;
	    if(!IsInside(i,j-1,onscreen[0],onscreen[1],onscreen[2],onscreen[3])){
	      first=onscreen[0];second=onscreen[1];
	      isdiagonal=true;
	    }
	    else if(!IsInside(i,j+1,onscreen[0],onscreen[1],onscreen[2],onscreen[3])){
	      first=onscreen[3];second=onscreen[2];
	      isdiagonal=true;
	    }
	    if(isdiagonal){
	      if(first.y==second.y)
		AddChar('-',0);
	      else{
		std::string str=",-'";
		bool reversed=false;
		if(first.x<second.x &&  first.y<second.y ||
		   first.x>second.x &&  first.y>second.y){
		  std::reverse(str.begin(),str.end());
		}
		AddChar(str[count],0);
		count++;
		if(count>=str.length())
		  count=str.length()-1;
	      }
	    }
	    else if(!IsInside(i-1,j,onscreen[0],onscreen[1],onscreen[2],onscreen[3])||
		    !IsInside(i+1,j,onscreen[0],onscreen[1],onscreen[2],onscreen[3]))
	      AddChar('|',0);
	    else
	      AddChar(' ',0);
      	  }
      	}
      }
    }
    for(auto ver:normalized){
      int x=width*(ver.x/abs(ver.w)+1)/2,y=height*(-ver.y/abs(ver.w)+1)/2;
      float z=ver.z/abs(ver.w);
      if(IsInSight(ver)){
	if(z>0){	  
	  MoveCursor(x,y);
	  if(x<0 || x>width || y<0 || y>height)
	    continue;
	  if(abs(z-zbuffer[x+y*width])<0.001){ // delete vertices because it looks nice
	    AddChar(' ',0);
	  }
	}
      }
    }
    
    for(auto ent:entities){
      auto ver=normalized[ent];
      if(!IsInSight(ver))
	continue;
      int x=width*(ver.x/abs(ver.w)+1)/2,y=height*(-ver.y/abs(ver.w)+1)/2;
      float z=ver.z/abs(ver.w);
      if(z<0 || z>zbuffer[x+width*y] || length(position-vertices[ent])>renderdistance)
	continue;
    }
  }
  float CalcZ(int x,int y,glm::vec3 a, glm::vec3 b,glm::vec3 c,glm::vec3 d){
    glm::vec3 pos(x,y,0);
    if(IsInsideTriangle(x,y,c,d,a)){
      b=d;// only use abc
    }
    glm::vec2 a1(a-c),b1(b-c);
    float mat[]={a1.x,a1.y,b1.x,b1.y};
    glm::mat2 T=glm::make_mat2(mat);
    glm::vec2 lambda2=glm::inverse(T)*(pos-c);
    glm::vec3 lambda3(lambda2,1-lambda2.x-lambda2.y);
    float del=0.0001;
    float a2=1.0/(a.z+del),b2=1.0/(b.z+del),c2=1.0/(c.z+del);
    float z=a.z*lambda3.x+b.z*lambda3.y+c.z*lambda3.z;
    return z;
  }
  
  bool IsInSight(glm::vec4 pos){
    return -pos.w<pos.x && -pos.w<pos.y && -pos.w<pos.z && pos.x<pos.w && pos.y<pos.w && pos.z<pos.w;
  }
  bool IsInside(int x,int y,glm::vec2 a,glm::vec2 b,glm::vec2 c,glm::vec3 d){
    return (IsInsideTriangle(x,y,a,b,c) || IsInsideTriangle(x,y,a,c,d));
  }
  bool IsInsideTriangle(int x,int y,glm::vec2 v1,glm::vec2 v2,glm::vec2 v3){
    glm::vec2 pt(x,y);
    float wv1=((v2.y-v3.y)*(pt.x-v3.x)+(v3.x-v2.x)*(pt.y-v3.y)) / ((v2.y-v3.y)*(v1.x-v3.x)+(v3.x-v2.x)*(v1.y-v3.y));
    float wv2=((v3.y-v1.y)*(pt.x-v3.x)+(v1.x-v3.x)*(pt.y-v3.y)) / ((v2.y-v3.y)*(v1.x-v3.x)+(v3.x-v2.x)*(v1.y-v3.y));
    float wv3 = 1.0f - wv1 - wv2;

    int one = (wv1 < -0.001);
    int two = (wv2 < -0.001);
    int three = (wv3 < -0.001);

    //is the point in the triangle
    return ((one == two) && (two == three));
  }

};
