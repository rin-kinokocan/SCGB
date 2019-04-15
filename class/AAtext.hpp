#pragma once
#include "DrawingComponent.hpp"
#include "AAfile.hpp"

namespace scgb{
  class AAtext :public DrawingComponent{
    // Draws Ascii Art (with Unicode chars).
  public:
    void Draw(){
      InitDraw();
      if(!aafile){
	Util::LogToStdout("file not found");
	return;
      }
      auto data=aafile->GetString();
      AddStr(data,0);
    }
    void SetAAfile(AAfile &aa){
      aafile=&aa;
    }
  protected:
    AAfile* aafile=nullptr;
  };
}
