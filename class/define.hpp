#pragma once
#include <ncurses.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <memory>
#include <map>
#include <string>
int mk_wcwidth(wchar_t);
int mk_wcswidth(const wchar_t,size_t);

namespace scgb{
  enum State{
    STA_DESTROY=0,
    STA_OPEN=1,
  };

  enum KeyEvent{
    //key values used in SCGB.
    SCGB_BACKSPACE,
    SCGB_DELETE,
    SCGB_CTR_D,
    SCGB_RIGHT=KEY_RIGHT,
    SCGB_LEFT=KEY_LEFT,
    SCGB_UP=KEY_UP,
    SCGB_DOWN=KEY_DOWN,
    SCGB_RESIZE=KEY_RESIZE,
    SCGB_NOINPUT=ERR,
    SCGB_QUIT='q',
  };

  enum Event{
    EVE_END,
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
