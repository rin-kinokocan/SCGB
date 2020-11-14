#pragma once
#include "scgb.hpp"
#include "MapData.hpp"
using namespace scgb;
using namespace std;

class MapBox:public DrawingComponent{
  MapData& map;
public:
  MapBox(MapData& md,int x,int y):map(md),DrawingComponent(x,y){
    SetTransparency(true);
    auto size=md.GetSize();
    width=size[0];
    height=size[1];
  }
 void Draw(){
   MoveCursor(0,0);
   auto size=map.GetSize();
   wchar_t res;
   for(int j=0;j<size[1];j++){
     for(int i=0;i<size[0];i++){
       int bit=0;
       if(map.GetFloor(i,j)==0){
	 AddChar(L' ',0);
	 continue;
       }
       if(map.GetFloor(i-1,j)==1)
	 bit|=1<<0;
       if(map.GetFloor(i+1,j)==1)
	 bit|=1<<1;
       if(map.GetFloor(i,j-1)==1)
	 bit|=1<<2;
       if(map.GetFloor(i,j+1)==1)
	 bit|=1<<3;
       switch(bit){
       case 0:
	 break;
       case 1:
	 res=L'╴';
	 break;
       case 2:
	 res=L'╶';
	 break;
       case 3:
	 res=L'─';
	 break;
       case 4:
	 res=L'╵';
	 break;
       case 5:
	 res=L'┘';
	 break;
       case 6:
	 res=L'└';
	 break;
       case 7:
	 res=L'┴';
	 break;
       case 8:
	 res=L'╷';
	 break;
       case 9:
	 res=L'┐';
	 break;
       case 10:
	 res=L'┌';
	 break;
       case 11:
	 res=L'┬';
	 break;
       case 12:
	 res=L'│';
	 break;
       case 13:
	 res=L'┤';
	 break;
       case 14:
	 res=L'├';
	 break;
       case 15:
	 res=L'┼';
	 break;
       defalut:
	 break;
       }
       auto pos=map.GetPosition();
       if(i==pos[0] && j==pos[1]){
	 wchar_t arrow;
	 switch(map.GetFacing()){
	 case 0:
	   arrow=L'^';
	   break;
	 case 1:
	   arrow=L'>';
	   break;
	 case 2:
	   arrow=L'v';
	   break;
	 case 3:
	   arrow=L'<';
	   break;
	 }
	 AddChar(arrow,0);
       }
       else
	 AddChar(res,0);
     }
     AddChar('\n',0);
   }
  }
};
