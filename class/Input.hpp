#pragma once
#include <curses.h>
#include <vector>

namespace scgb{
  class Input{
  private:
    WINDOW* window;
  public:
    std::vector<int> GetInput(){
      std::vector<int> ret{0,ERR};
      wint_t tmp_in; int tmp_code;
      while(true){
      	tmp_code=wget_wch(window,&tmp_in);
      	if(tmp_code==ERR)
      	  break;
      	else{
      	  ret[0]=tmp_in;
      	  ret[1]=tmp_code;
      	}
      }
      return ret;
    }
    
    Input(){
      window=newwin(1,1,0,0);
      nodelay(window,true);
      keypad(window,true);
    }
    ~Input(){
      delwin(window);
    }
    
  };
}
