#pragma once
#include <vector>
#include <string>

int mk_wcwidth(wchar_t);
int mk_wcswidth(const wchar_t*,size_t);

namespace scgb{
  
  class Vector2D:public std::vector<int>{
  public:
    Vector2D():std::vector<int>(2){}
    Vector2D(int x,int y):Vector2D(){
      (*this)[0]=x;(*this)[1]=y;
    }
  };
  
  class RGBvalue:public std::vector<short>{
  public:
    RGBvalue():std::vector<short>(3){}
    RGBvalue(int x,int y,int z):RGBvalue(){
      (*this)[0]=x;(*this)[1]=y;(*this)[2]=z;
    }
  };
  
  //prototypes of Util functions
  namespace Util{
    Vector2D GetMaxScr();
    void LogToStdout(std::string);
    void ShowColorPairs();
  }
}
