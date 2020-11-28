#pragma once
#include "scgb.hpp"
#include "Scene.hpp"
#include "TestScene.hpp"
#include "ColorTestScene.hpp"
using namespace scgb;
using namespace std;

class TitleScene:public Scene{
protected:
  int curpos=0;
  const static int cursor=2;
public:
  TitleScene(int x=0,int y=0){
    Add(Image("assets/Logo.bmp",x+0,y+0));
    Add(AABox("assets/TitleLogo.txt",x+1,y+1))->SetTransparency(true);
    Add(TextBox<std::wstring>(L"*",x+19,y+11));
    Add(TextBox<std::wstring>(L"Play Game",x+20,y+11));
    Add(TextBox<std::wstring>(L"Color Test",x+20,y+12));
    Add(TextBox<std::wstring>(L"Quit Game",x+20,y+13));    
  }
  void Update(){}
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
      if(curpos==1)
	gc.ChangeScene(make_shared<ColorTestScene>(x,y));
      else if(curpos==2)
	gc.EndGame();
      else
	gc.ChangeScene(make_shared<TestScene>(x,y));
      break;
    default:
      break;
    }
  }
};
