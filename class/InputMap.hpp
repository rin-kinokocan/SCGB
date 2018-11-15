#pragma once
#include "define.hpp"

namespace scgb{
  class InputMap{
  private:
    std::map<KeyEvent,bool> map;
  public:
    void Update(){
      for(auto& i:map){
      	i.second=false;
      }
      while(1){
	wint_t c;
      	wget_wch(stdscr,&c);
	if(c!=SCGB_NOINPUT){
	  auto i=map.find((KeyEvent)c);
	  if(i==map.end()){
      	    map.insert(std::pair<KeyEvent,bool>((KeyEvent)c,true));
      	  }
      	  else{
      	    if(i->second==false)
      	      i->second=true;
	    auto i=map.find((KeyEvent)c);
	    if(i!=map.end()){
	      if(i->second==false)
		i->second=true;
	      else
		break;
	    }
	    else
	      map.insert(std::pair<KeyEvent,bool>((KeyEvent)c,true));
	  }
	}
      }
    };
    
    bool GetBool(KeyEvent k){
      if(map.find(k)!=map.end())
	return map.find(k)->second;
      else
	return false;
    };
  };
}
