#include "define.h"
#include <csignal>

namespace scgb{
  namespace Util{
    cChar make_cChar(wchar_t in,int attr){
      //make cchar_t from single wchar_t
      cChar re;
      re.chars[0]=in;
      re.chars[1]='\0';
      re.attr=attr;
      return re;
    }
    wchar_t cCharToWchar(cChar c){
      return c.chars[0];
    }
    int cCharToAttr(cChar c){
      return c.attr;
    }

    Vector2D GetMaxScrXY(){
      int x,y;getmaxyx(stdscr,y,x);
      Vector2D v;
      v.resize(2);
      v[0]=x;v[1]=y;
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
      signal(SIGWINCH,ResizeHandler);
      //to detect Ctrl-c
      signal(SIGQUIT,InterruptHandler);
    }
  }
}
