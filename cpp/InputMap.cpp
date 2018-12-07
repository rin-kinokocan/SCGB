#include "InputMap.hpp"

using namespace scgb;

static inline bool IsSpecialKey(wint_t c){
  switch(c){
  case 0:
  case 10:
  case 127:
    return true;
  default:
    break;
  }
  return false;
}

void InputMap::Update(){
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
    if(code!=KEY_CODE_YES && !IsSpecialKey(c)){
      input+=c;
    }
  }
}

bool InputMap::GetBool(wint_t k){
  if(map.find(k)!=map.end())
    return map.find(k)->second;
  else
    return false;
}

