#include "scgb.hpp"
#include "GameContext.hpp"
#include <iostream>
#include <map>
using namespace scgb;
using namespace std;
#include <unistd.h>
void Dev_CheckPalette(){
  clear();
  move(0,0);
  for(int i=0;i<COLOR_PAIRS;i++){
    attron(COLOR_PAIR(i));
    addch('@');
    attroff(COLOR_PAIR(i));
  }
  refresh();
  sleep(10000);
}

class Map{
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
      string sval;
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
  Map(std::string f,int x,int y):x(x),y(y){
    LoadFile(f);
  }
};

class Toach:public CompositeDrawingComponent{
public:
  Toach(int x,int y){
    Color& c=Color::GetInstance();
    auto outer=c.GetColor(200,0,0);
    auto inner=c.GetColor(255,200,0);
    auto outerpair=c.GetColorPair(200,0,0);
    auto wood=c.GetColorPair(173,113,68);
    init_pair(outerpair,inner,outer);
    auto imf=std::make_shared<HandMadeImageFile>(3,4);
    attr_t att=COLOR_PAIR(outerpair)|A_BOLD;
    imf->Add(1,1,att)->Add(0,2,att)->Add(1,2,att)->Add(2,2,att)->Add(0,3,COLOR_PAIR(wood));
    Add(Image(imf,x,y))->SetTransparency(true);
    Add(Animation("assets/TestAnimation.txt",2,x,y))->SetTransparency(true);
  }
};

class Coin :public CompositeDrawingComponent{
public:
  Coin(int x,int y){
    Color& c=Color::GetInstance();
    auto base=c.GetColor(255, 227, 48);
    auto pair=c.GetColorPair(255,227,48);
    init_pair(pair,0,base);
    auto imf=std::make_shared<HandMadeImageFile>(9,9);
    attr_t att=COLOR_PAIR(pair)|A_BOLD;
    for(int i=0;i<9;i++){
      for(int j=1;j<7;j++){
	imf->Add(i,j,att);
      }
    }
    imf->Add(0,1,A_BOLD)->Add(8,1,A_BOLD)->Add(0,6,A_BOLD)->Add(8,6,A_BOLD);
    Add(Image(imf,x,y))->SetTransparency(true);
    Add(AABox("assets/Coin.txt",x,y))->SetTransparency(true);    
  }
};

class MainScreen:public Scene{
protected:
  Map map;
  std::wstring message=L"COIN GAINED:";
  int coin=0;
public:
  MainScreen(int x=0,int y=0):map("assets/Map.txt",0,0){
    Add(AABox("assets/LeftWallBetween.txt",x,y));//1
    Add(AABox("assets/LeftWallBetween2.txt",x+3,y+3));//2
    Add(AABox("assets/LeftWall1.txt",x,y));//3
    Add(AABox("assets/LeftWall2.txt",x+2,y+1));//4
    Add(AABox("assets/RightWallBetween.txt",x+27,y));//5
    Add(AABox("assets/RightWallBetween2.txt",x+22,y+3));//6
    Add(AABox("assets/RightWall1.txt",x+27,y));//7
    Add(AABox("assets/RightWall2.txt",x+22,y+1));//8
    Add(AABox("assets/FrontWall2.txt",x+7,y+3));//9
    Add(AABox("assets/FrontWall1.txt",x+2,y));//10
    Add(Coin(x+11,y+4));
    Add(MessageWindow(message,0,1,15,50,10));
  }
  
  void Draw(){
    message=L"COIN GAINED:"+std::to_wstring(coin);
    int sight=map.GetSight(),count=0;
    for(int i=0;i<10;i++){
      int num=1<<i;
      if(sight&num){
	composite[i]->Draw();
      }
    }
    if(map.GetCoin()){
      composite[10]->Draw();
    }
    for(auto i:composite){
      if(count>10)
	i->Draw();
      count++;
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
    auto pos=map.GetPosition();
    if(map.GetIcon(pos[0],pos[1])==1){
      map.SetIcon(pos[0],pos[1],0);
      coin++;
    }
  }
};
class TitleScreen:public Scene{
protected:
  int curpos=0;
  const static int cursor=2;
public:
  TitleScreen(int x=0,int y=0){
    Add(Image("assets/Logo.bmp",x+0,y+0));
    Add(AABox("assets/TitleLogo.txt",x+1,y+1));
    Add(TextBox<wstring>(L"*",x+19,y+11));
    Add(TextBox<wstring>(L"New Game",x+20,y+11));
    Add(TextBox<wstring>(L"Load Game",x+20,y+12));
    Add(TextBox<wstring>(L"Quit Game",x+20,y+13));
  }
  void HandleInput(GameContext& gc,wint_t input,int code){
    switch(input){
    case KEY_UP:
      if(curpos>0){
	composite[cursor]->Move(0,-1);
	curpos--;
      }
      else{
	composite[cursor]->Move(0,2);
	curpos=2;
      }
      break;
    case KEY_DOWN:
      if(curpos<2){
	composite[cursor]->Move(0,1);
	curpos++;
      }
      else{
	composite[cursor]->Move(0,-2);
	curpos=0;
      }
      break;
    case KEY_ENTER:
    case '\n':
      if(curpos==2)
	gc.EndGame();
      else
	gc.ChangeScene(make_shared<MainScreen>(x,y));
      break;
    default:
      break;
    }
  }
};

int main(){
  bool isend=false;
  // All envioromental things
  CursesManager& cm=CursesManager::GetInstance();
  Color& col=Color::GetInstance();
  Clock clock(20);
  //GameContext
  GameContext gc;
  gc.ChangeScene(make_shared<TitleScreen>(1,1));
  while(!isend){
    clear();
    wint_t input;
    auto code=get_wch(&input);
    switch(input){
    case KEY_RESIZE:
      cm.OnResize();
      break;
    default:
      break;
    }
    if(gc.IsEnd())
      break;
    gc.HandleInput(input,code);
    gc.Draw();
    refresh();
    clock.WaitFrame();
  }
  return 0;
}
