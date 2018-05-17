#pragma once
#include "define.h"

using namespace std;

namespace scgb{
  class Screen{
    //initializes ncurses and creates a window.
  public:
    template <class T>
    static shared_ptr<T> AddDrawable(Layer l,T* pd){
      if(Screen::drawentity.find(l)==Screen::drawentity.end()){
	shared_ptr<T> b;
	b.reset(pd);
	Screen::drawentity.insert(std::pair<Layer,pBaseWindow>(l,b));
	return b;
      }
      else{
	string info="the layer ";
	info+=l;info+="is already used";
	endwin();
	throw new runtime_error(info);
      }
    }


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
