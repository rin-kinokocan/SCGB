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
  int GetColWalls(int x,int y){
    int index=Size[1]*x+y;
    if(index<0 || index>ColWalls.size())
      return 0;
    return ColWalls[index];
  }
  int GetRowWalls(int x,int y){
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
  std::vector<int> GetPosition(){
    std::vector<int> vec{x,y};
    return vec;
  }
  void MoveForward(){
    switch(facing){
    case 0:
      if(GetRowWalls(x,y)==0)
	y--;
      break;
    case 1:
      if(GetColWalls(x+1,y)==0)
	x++;
      break;
    case 2:
      if(GetRowWalls(x,y+1)==0)
	y++;
      break;
    case 3:
      if(GetColWalls(x,y)==0)
	x--;
      break;
    }
  }
  
  int SetIcon(int x,int y,int i){
    int index=x*Size[1]+y;
    if(index<0 || index>Icons.size())
      return 0;
    Icons[index]=i;
    return 1;
  }
  
  int GetCoin(){
    int res=0;
    switch(facing){
    case 0:
      res=GetIcon(x,y-1);
      break;
    case 1:
      res=GetIcon(x+1,y);
      break;
    case 2:
      res=GetIcon(x,y+1);
      break;
    case 3:
      res=GetIcon(x-1,y);
      break;
    default:
      break;
    }
    return res;
  }
  
  int GetLW1(){
    int res=0;
    switch(facing){
    case 0:
      res=GetColWalls(x,y);
      break;
    case 1:
      res=GetRowWalls(x,y);
      break;
    case 2:
      res=GetColWalls(x+1,y);
      break;
    case 3:
      res=GetRowWalls(x,y+1);
      break;
    default:
      break;
    }
    return res;
  }
  int GetLW2(){
    int res=0;
    switch(facing){
    case 0:
      res=GetColWalls(x,y-1);
      break;
    case 1:
      res=GetRowWalls(x+1,y);
      break;
    case 2:
      res=GetColWalls(x+1,y+1);
      break;
    case 3:
      res=GetRowWalls(x-1,y+1);
      break;
    default:
      break;
    }
    return res;
  }
  int GetLWB1(){
    int res=0;
    switch(facing){
    case 0:
      res=GetRowWalls(x-1,y);
      break;
    case 1:
      res=GetColWalls(x+1,y-1);
      break;
    case 2:
      res=GetRowWalls(x+1,y+1);
      break;
    case 3:
      res=GetColWalls(x,y+1);
      break;
    default:
      break;
    }
    return res;
  }
  int GetLWB2(){
    int res=0;
    switch(facing){
    case 0:
      res=GetRowWalls(x-1,y-1);
      break;
    case 1:
      res=GetColWalls(x+2,y-1);
      break;
    case 2:
      res=GetRowWalls(x+1,y+2);
      break;
    case 3:
      res=GetColWalls(x-1,y+1);
      break;
    default:
      break;
    }
    return res;
  }
  int GetRW1(){
    int res=0;
    switch(facing){
    case 0:
      res=GetColWalls(x+1,y);
      break;
    case 1:
      res=GetRowWalls(x,y+1);
      break;
    case 2:
      res=GetColWalls(x,y);
      break;
    case 3:
      res=GetRowWalls(x,y);
      break;
    default:
      break;
    }
    return res;
  }
  int GetRW2(){
    int res=0;
    switch(facing){
    case 0:
      res=GetColWalls(x+1,y-1);
      break;
    case 1:
      res=GetRowWalls(x+1,y+1);
      break;
    case 2:
      res=GetColWalls(x,y+1);
      break;
    case 3:
      res=GetRowWalls(x-1,y);
      break;
    default:
      break;
    }
    return res;
  }
  int GetRWB1(){
    int res=0;
    switch(facing){
    case 0:
      res=GetRowWalls(x+1,y);
      break;
    case 1:
      res=GetColWalls(x+1,y+1);
      break;
    case 2:
      res=GetRowWalls(x-1,y+1);
      break;
    case 3:
      res=GetColWalls(x,y-1);
      break;
    default:
      break;
    }
    return res;
  }
  int GetRWB2(){
    int res=0;
    switch(facing){
    case 0:
      res=GetRowWalls(x+1,y-1);
      break;
    case 1:
      res=GetColWalls(x+2,y+1);
      break;
    case 2:
      res=GetRowWalls(x-1,y+2);
      break;
    case 3:
      res=GetColWalls(x-1,y-1);
      break;
    default:
      break;
    }
    return res;
  }
  int GetFW1(){
    int res=0;
    switch(facing){
    case 0:
      res=GetRowWalls(x,y);
      break;
    case 1:
      res=GetColWalls(x+1,y);
      break;
    case 2:
      res=GetRowWalls(x,y+1);
      break;
    case 3:
      res=GetColWalls(x,y);
      break;
    default:
      break;
    }
    return res;
  }
  int GetFW2(){
    int res=0;
    switch(facing){
    case 0:
      res=GetRowWalls(x,y-1);
      break;
    case 1:
      res=GetColWalls(x+2,y);
      break;
    case 2:
      res=GetRowWalls(x,y+2);
      break;
    case 3:
      res=GetColWalls(x-1,y);
      break;
    default:
      break;
    }
    return res;
  }
  
  int GetSight(){
    int res=0;
    if(GetLWB1()==1)
      res|=1<<0;
    if(GetLWB2()==1)
      res|=1<<1;
    if(GetLW1()==1)
      res|=1<<2;
    if(GetLW2()==1)
      res|=1<<3;
    if(GetRWB1()==1)
      res|=1<<4;
    if(GetRWB2()==1)
      res|=1<<5;
    if(GetRW1()==1)
      res|=1<<6;
    if(GetRW2()==1)
      res|=1<<7;
    if(GetFW2()==1)
      res|=1<<8;
    if(GetFW1()==1)
      res|=1<<9;
    return res;
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
