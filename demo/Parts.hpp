#pragma once
#include "scgb.hpp"
using namespace scgb;
using namespace std;

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
    Add(Image(imf,x,y))->SetTransparency(false);
    Add(AABox("assets/Coin.txt",x,y))->SetTransparency(true);    
  }
};
