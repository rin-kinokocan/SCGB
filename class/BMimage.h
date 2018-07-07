#pragma once
#include "BaseWindow.h"

namespace scgb{
  class BMimage :public BaseWindow{
  protected:
    std::vector<int> Pixels;
  public:
    void Draw();
    BMimage(int,int,SizeData*,std::string);
  };
  
  class BMimageBuilder:public BWBuilder{
  protected:
    std::string filename;
  public:
    Drawable* GetResult(){
      return new BMimage(x,y,psd,filename);
    }
    BMimageBuilder(int x,int y,std::string fn)
      :BWBuilder(x,y,0,0){filename=fn;};
    virtual ~BMimageBuilder(){};
  };
}
