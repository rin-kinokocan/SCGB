#include "Scene.hpp"
using namespace scgb;
using namespace std;

class ColorTestScene:public Scene{
public:
  ColorTestScene(int x,int y):Scene(x,y){};
  void Draw(){
    move(0,0);
    for(int i=0;i<COLOR_PAIRS;i++){
      attron(COLOR_PAIR(i));
      addch('@');
      attroff(COLOR_PAIR(i));
    }
  }
  void Output(){
    endwin();
    short r,g,b;
    for(int i=0;i<COLORS;i++){
      color_content(i,&r,&g,&b);
      cout<<'('<<r<<','<<g<<','<<b<<')'<<endl;
    }
  }
  void Update(){}
  void HandleInput(GameContext& gc,wint_t input,int code){
    switch(input){
    case L'q':
      gc.EndGame();
    case L'c':
      Output();
    }
  }
};
