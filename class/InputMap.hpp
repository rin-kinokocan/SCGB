#pragma once
#include "define.hpp"

namespace scgb{
  class InputMap{
  private:
    std::map<wint_t,bool> map;
  public:
    void Update(){
      for(auto& i:map){
      	i.second=false;
      }
      while(1){
	wint_t c;
      	wget_wch(stdscr,&c);
	if(c!=ERR){
	  auto i=map.find(c);
	  if(i==map.end()){
      	    map.insert(std::pair<wint_t,bool>(c,true));
      	  }
      	  else{
      	    if(i->second==false)
      	      i->second=true;
	    auto i=map.find(c);
	    if(i!=map.end()){
	      if(i->second==false)
		i->second=true;
	      else
		break;
	    }
	    else
	      map.insert(std::pair<wint_t,bool>(c,true));
	  }
	}
      }
    };
    
    bool GetBool(wint_t k){
      if(map.find(k)!=map.end())
	return map.find(k)->second;
      else
	return false;
    };
  };
}
