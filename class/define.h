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

  enum Key{
    //key values used in SCGB.If your terminal returns other number,
    //then change these numbers accordingly.
    SCGB_BACKSPACE=127,
    SCGB_DELETE=KEY_DC,
    SCGB_CTR_D=4,
    SCGB_RIGHT=KEY_RIGHT,
    SCGB_LEFT=KEY_LEFT,
    SCGB_UP=KEY_UP,
    SCGB_DOWN=KEY_DOWN,
  };
  
  enum Event{
    //Return values of Screen::GetEvent.
    //I may merge this into Key.
    EVE_QUIT='q',
    EVE_PRINT='p',
    EVE_NOINPUT=ERR,    
    EVE_RESIZE=KEY_RESIZE,
    EVE_RIGHT=KEY_RIGHT,
    EVE_LEFT=KEY_LEFT,
    EVE_UP=KEY_UP,
    EVE_DOWN=KEY_DOWN,
  };

  enum Direction{
    Right,
    Left,
    Up,
    Down,
  };
      
  typedef struct{
    unsigned short bfType;
    unsigned int bfSize;
    unsigned short bfReserved1;
    unsigned short bfReserved2;
    unsigned int bfOffBits;
  }BMfile;

  typedef struct{
    unsigned int biSize;
    unsigned int biWidth;
    unsigned int biHeight;
    unsigned short biPlanes;
    unsigned short biBitCount;
    unsigned int biCompression;
    unsigned int biSizeImage;
    unsigned int biXPixPerMeter;
    unsigned int biYPixPerMeter;
    unsigned int biClrUsed;
    unsigned int biClrImporant;
  }BMinfo;



  typedef WINDOW* WinPtr;
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
    };
    WeakPtr(std::shared_ptr<T> a){
      pointer=a;
    };
  };

  typedef cchar_t cChar;
  
  //prototypes of Util functions
  namespace Util{
    cChar make_cChar(wchar_t in,int attr);
    wchar_t cCharToWchar(cChar c);
    int cCharToAttr(cChar c);
    Vector2D GetMaxScrXY();
    void LogToStdout(std::string);
  }
}

