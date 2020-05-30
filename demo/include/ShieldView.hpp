#pragma once
#include "Shield.hpp"
#include "DrawingComponent.hpp"

namespace Invader{
  class ShiledView:public scgb::DrawingComponent{
  private:
    Shield* shield;
    attr_t attr=0;
  public:
    ShieldView(Shield &s){
      shield=&s;
    }
    void Draw(){
      auto a=shield->GetSize();
      InitDraw();
      for(int i=0;i<a[0];i++){
	for(int j=0;j<a[1];j++){
	  switch(shield->GetDamage(i,j)){
	  case 0:
	    AddChar(L' ',attr);
	    break;
	  case 1:
	    AddChar(L'◇',attr);
	    break;
	  case 2:
	    AddChar(L'■',attr);
	    break;
	  default:
	    AddChar(L'?',attr);
	    break;
	  }
	}
	ChangeLine();
      }
    };
  };
}
