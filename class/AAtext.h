#pragma once
#include "BaseWindow.h"

namespace scgb{
  class AAtext :public BaseWindow{
  protected:
    std::vector<wchar_t> data;
  public:
    void Draw();
    AAtext(int x,int y,SizeData*,std::string);
  };
  class AAtextBuilder:public BWBuilder{
  protected:
    std::string filename;
  public:
    Drawable* GetResult(){
      return new AAtext(x,y,psd,filename);
    }
    AAtextBuilder(int x,int y,std::string fn)
      :BWBuilder(x,y,0,0){filename=fn;};
    virtual ~AAtextBuilder(){};
  };
}
