#pragma once
#include "define.h"

using namespace std;

namespace scgb{
  class Screen{
    //initializes ncurses and creates a window.
  public:
    static bool AddDrawable(Layer l,pBaseWindow pb){
      if(Screen::drawentity.find(l)==Screen::drawentity.end())
	Screen::drawentity.insert(std::pair<Layer,pBaseWindow>(l,pb));
      else
	return false;
      return true;	 
    };
    static Vector2D GetMaxXY();
    static cchar_t GetCchar(int x,int y);
    static void AddCchar(cchar_t,unsigned int x,unsigned int y);
    static Event GetEvent();    
    static State GetState();
    static void Draw();
    static void Resize();
    static void Destroy();
    static void Refresh();
    static void Init();
  private:
    //static variables
    static State state;
    static DrawList drawentity;    
    static vector<cchar_t> wholeScreen;
    //Signal handlers
    static void ResizeHandler(int param);
    static void InterruptHandler(int param);
  };

}
