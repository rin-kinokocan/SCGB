#pragma once
#include "define.h"
namespace scgb{
  class InputMap{
  private:
    std::map<KeyEvent,bool> map;
  public:
    void Update(){
      for(auto& i:map){
	i.second=false;
      }
      bool flag=true;
      while(flag){
	int c=getch();
	auto i=map.find((KeyEvent)c);
	if(c!=SCGB_NOINPUT){
	  if(i==map.end()){
	    map.insert(std::pair<KeyEvent,bool>((KeyEvent)c,true));
	  }
	  else{
	    if(i->second==false)
	      i->second=true;
	    else
	      flag=false;
	  }
	}
	else
	  flag=false;
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
