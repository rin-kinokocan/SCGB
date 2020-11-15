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
  void Update(){}
  void HandleInput(GameContext& gc,wint_t input,int code){
    switch(input){
    case L'q':
      gc.EndGame();
    }
  }
};
