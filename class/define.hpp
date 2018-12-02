#pragma once
#include "curses.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <memory>
#include <map>
#include <string>
int mk_wcwidth(wchar_t);
int mk_wcswidth(const wchar_t*,size_t);

namespace scgb{
  enum State{
    STA_DESTROY=0,
    STA_OPEN=1,
  };

  enum Event{
    EVE_END,
    EVE_ENDINPUT,
  };
  
  enum Direction{
    Right,
    Left,
    Up,
    Down,
  };
  
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
  
  template <class T>
  class WeakPtr{//wrapper of std::weak_ptr
  public:
    std::weak_ptr<T> pointer;
    std::shared_ptr<T> operator->(){
      if(!pointer.expired())
	return pointer.lock();
      else
	throw std::runtime_error("NOPE.");
    }
    WeakPtr(){}
    WeakPtr(std::shared_ptr<T> a){
      pointer=a;
    }
  };

  //prototypes of Util functions
  namespace Util{
    int GetAttr(cchar_t c);
    Vector2D GetMaxScr();
    void LogToStdout(std::string);
    void SetSigHandlers();
  }
}
