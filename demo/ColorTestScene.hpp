#include "Scene.hpp"
#include "Parts.hpp"
using namespace scgb;
using namespace std;

class ColorTestScene:public Scene{
public:
  ColorTestScene(int x,int y):Scene(x,y){Add(Image("assets/kinoko.bmp",-4,y));Add(Coin(-10,y))->SetTransparency(true);};
  void Draw(){
    move(0,0);
    for(int i=0;i<COLOR_PAIRS;i++){
      attron(COLOR_PAIR(i));
      addch('@');
      attroff(COLOR_PAIR(i));
    }
    composite[0]->Draw();
    composite[0]->Move(1,1);
    composite[1]->Draw();
    composite[1]->Move(1,0);
  }
  void Output(){
    endwin();
    short r,g,b;
    cout<<"can_change_color:"<<(bool)can_change_color()<<endl;
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
