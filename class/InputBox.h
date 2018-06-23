#pragma once
#include "WindowContainer.h"

namespace scgb{
  class InputBox:public WindowContainer{
  private:
    int x,y,w,h;
    std::vector<cChar> info;
  public:
    void Draw();
    // std::vector<wchar_t> GetInput();
    InputBox(int,int,int,int,SizeData*,std::string);
  };
  
  class IBBuilder:public DrawableBuilder{
  protected:
    std::string str;
  public:
    virtual Drawable* GetResult(){
      return new InputBox(x,y,w,h,psd,str);
    }
    IBBuilder(int x,int y,int w,int h,std::string s)
      :DrawableBuilder(x,y,w,h){str=s;};
    virtual ~IBBuilder(){};
  };
}
