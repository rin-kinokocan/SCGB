#pragma once
#include <ncurses.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <memory>
#include <map>
#include <string>

namespace scgb{
  //forward declaration of classes
  class Drawable;
  class BaseWindow;
  class WindowContainer;
  //
  enum State{
    STA_DESTROY=0,
    STA_OPEN=1,
  };

  enum KeyEvent{
    //key values used in SCGB.
    SCGB_BACKSPACE,
    SCGB_DELETE,
    SCGB_CTR_D,
    SCGB_RIGHT,
    SCGB_LEFT,
    SCGB_UP,
    SCGB_DOWN,
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
      
  typedef std::ifstream File;
  typedef std::wifstream WFile;

  typedef std::shared_ptr<scgb::Drawable> pDrawable;
  typedef std::vector<int> Vector2D;
  
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

  typedef cchar_t cChar;
  
  //prototypes of Util functions
  namespace Util{
    cChar make_cChar(wchar_t in,int attr);
    wchar_t cCharToWchar(cChar c);
    int cCharToAttr(cChar c);
    Vector2D GetMaxScrXY();
    void LogToStdout(std::string);
    void SetSigHandlers();
  }
}
