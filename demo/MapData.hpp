#pragma once
#include <vector>
#include <string>
using namespace scgb;
using namespace std;

class MapData{
  // Stores Map data and current player status.
private:
  std::vector<int> Size;
  std::vector<int> RowWalls;
  std::vector<int> ColWalls;
  std::vector<int> Floors;
  std::vector<int> Icons;
  int facing=0;// 0123->NWSE
  int x=0,y=0;// position
public:
  int GetFacing(){
    return facing;
  }
  
  void TurnLeft(){
    if(facing==0)
      facing=3;
    else
      facing--;
  }
  void TurnRight(){
    if(facing==3)
      facing=0;
    else
      facing++;
  }

  vector<int>& GetFloors(){
    return Floors;
  }

  vector<int>& GetColWalls(){
    return ColWalls;
  }
  vector<int>& GetRowWalls(){
    return RowWalls;
  }
  
  int GetColWall(int x,int y){
    int index=Size[1]*x+y;
    if(index<0 || index>ColWalls.size())
      return 0;
    return ColWalls[index];
  }
  
  int GetRowWall(int x,int y){
    int index=(Size[1]+1)*x+y;
    if(index<0 || index>RowWalls.size()){
      return 0;
    }
    return RowWalls[index];
  }

  int GetFloor(int x,int y){
    int index=x*Size[1]+y;
    if(index<0 || index>Floors.size())
      return 0;
    return Floors[index];
  }
  
  int GetIcon(int x,int y){
    int index=x*Size[1]+y;
    if(index<0 || index>Icons.size())
      return 0;
    return Icons[index];
  }

  std::vector<int> GetSize(){
    return Size;
  }
  std::vector<int> GetPosition(){
    std::vector<int> vec{x,y};
    return vec;
  }
  
  bool MoveForward(){
    switch(facing){
    case 0:
      if(GetRowWall(x,y)==0){
	y--;
	return true;
      }
      break;
    case 1:
      if(GetColWall(x+1,y)==0){
	x++;
	return true;
      }
      break;
    case 2:
      if(GetRowWall(x,y+1)==0){
	y++;
	return true;
      }
      break;
    case 3:
      if(GetColWall(x,y)==0){
	x--;
	return true;
      }
      break;
    }
    return false;
  }
  bool MoveBackward(){
    switch(facing){
    case 0:
      if(GetRowWall(x,y+1)==0){
	y++;
	return true;
      }
      break;
    case 1:
      if(GetColWall(x,y)==0){
	x--;
	return true;
      }
      break;
    case 2:
      if(GetRowWall(x,y)==0){
	y--;
	return true;
      }
      break;
    case 3:
      if(GetColWall(x+1,y)==0){
	x++;
	return true;
      }
      break;
    }
    return false;
  }
  
  int SetIcon(int x,int y,int i){
    int index=x*Size[1]+y;
    if(index<0 || index>Icons.size())
      return 0;
    Icons[index]=i;
    return 1;
  }
  
  void LoadFile(std::string filename){
    std::ifstream file(filename);
    if(!file.is_open())
      throw std::runtime_error("Cannot Open file :"+filename);
    
    std::string line;
    int i=0;
    while(std::getline(file,line)){
      std::stringstream ss(line);
      std::string sval;
      int val=0;
      while(std::getline(ss,sval,',')){
	val=std::stoi(sval);
	switch(i){
	case 0:
	  Size.push_back(val);
	  break;
	case 1:
	  RowWalls.push_back(val);
	  break;
	case 2:
	  ColWalls.push_back(val);
	  break;
	case 3:
	  Floors.push_back(val);
	  break;
	case 4:
	  Icons.push_back(val);
	  break;
	default:
	  break;
	}
      }
      i++;
    }
  }
  MapData(std::string f,int x,int y):x(x),y(y){
    LoadFile(f);
  }
};
