#include "define.hpp"
#include <csignal>

namespace scgb{
  namespace Util{
    Vector2D GetMaxScr(){
      Vector2D v;
      getmaxyx(stdscr,v[1],v[0]);
      return v;
    }
    
    void LogToStdout(std::string a){
      bool f=true;
      if(isendwin())
      	f=false;
      else
	endwin();
      std::cout<<a<<std::endl;
      if(f)
	initscr();
    }
  }
}
