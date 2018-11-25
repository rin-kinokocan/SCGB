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
    
    static void ResizeHandler(int param){
      if(isendwin()==false){
	ungetch(scgb::SCGB_RESIZE);
      }
    }
    
    static void InterruptHandler(int param){
    }

    void SetSigHandlers(){
      //if ncurses hasn't enabled sigwinch.
      //signal(SIGWINCH,ResizeHandler);
      //to detect Ctrl-c
      signal(SIGQUIT,InterruptHandler);
    }
  }
}
