#pragma once
#include "define.h"
#include "Drawable.h"

namespace scgb{
  class Screen{
    //initializes ncurses and creates a window.
  public:
    template <class T>
    static WeakPtr<T> AddDrawable(int l,T* pd){
      if(Screen::drawentity.find(l)==Screen::drawentity.end()){
	std::shared_ptr<T> b;
	b.reset(pd);
	Screen::drawentity.insert(std::pair<int,pDrawable>(l,b));
	return WeakPtr<T>(b);
      }
      else{
	std::string info="the layer ";
	info+=l;info+="is already used";
	endwin();
	throw new std::runtime_error(info);
      }
      Draw();//updates screen
    };
    static void DeleteDrawable(int l);
    static Vector2D GetMaxXY();
    static cchar_t GetCchar(int x,int y);
    static void AddCchar(cchar_t,unsigned int x,unsigned int y);
    static Event GetEvent();    
    static State GetState();
    static void Draw();
    static void Resize();
    static void Destroy();
    static void Refresh();
    static void Init();//The most important method.
  private:
    //static variables
    static State state;
    static std::map<int,scgb::pDrawable> drawentity;    
    static std::vector<cchar_t> wholeScreen;
    //Signal handlers
    static void ResizeHandler(int param);
    static void InterruptHandler(int param);
    Screen();
  };

}
