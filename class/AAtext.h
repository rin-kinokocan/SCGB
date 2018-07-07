#pragma once
#include "BaseWindow.h"

namespace scgb{
  class AAtext :public BaseWindow{
  protected:
    std::vector<wchar_t> data;
  public:
    void Draw();
    AAtext(double x,double y,SizeData*,std::string);
  };
  
  class AAtextBuilder:public BWBuilder{
  protected:
    std::string filename;
  public:
    Drawable* GetResult(){
      return new AAtext(x,y,psd,filename);
    }
    AAtextBuilder(double x,double y,std::string fn)
      :BWBuilder(x,y,0,0){filename=fn;};
    virtual ~AAtextBuilder(){};
  };
}
