#pragma once
#include "define.hpp"

namespace scgb{
  class InputMap{
  private:
    std::map<wint_t,bool> map;
    wint_t input;
  public:
    void Update(){
      for(auto& i:map){
      	i.second=false;
      }
      while(1){
	wint_t c;
	auto code=get_wch(&c);
	if(code==ERR)
	  break;
	if(code==KEY_CODE_YES || (int)c<256){
	  auto i=map.find(c);
	  if(i==map.end()){
	    map.insert(std::pair<wint_t,bool>(c,true));
	  }
	  else{
	    if(i->second==false)
	      i->second=true;
	  }
	}
	else{
	  input=c;
	  break;
	}
      }
    };
    
    bool GetBool(wint_t k){
      if(map.find(k)!=map.end())
	return map.find(k)->second;
      else
	return false;
    };
    wint_t GetLastInput(){
      return input;
    }
  };
}
