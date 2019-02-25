#pragma once
#include "BaseView.hpp"
#include "Attribute.hpp"

namespace scgb{
  class Block:public BaseView{
  public:
    void Draw(){
      MoveCursor(0,0);
      auto geo=wi.geometry->GetData();
      for(int i=0;i<geo[0]*geo[1];i++){
	AddChar(L' ',attribute->GetData());
      }
    }
        
    Block(WindowInfo wi,std::shared_ptr<Attribute> attr)
      :BaseView(wi){
      attribute=attr;
    }
			 
  protected:
    std::shared_ptr<Attribute> attribute;
  };
}
