#pragma once
#include <ncurses.h>
#include <vector>
#include <fstream>
#include <iostream>

namespace scgb{  
  enum State{
    STA_DESTROY=0,
    STA_OPEN=1,
  };
  
  enum Event{
    EVE_QUIT='q',
    EVE_PRINT='p',
    EVE_NOINPUT=ERR,    
    EVE_RESIZE=KEY_RESIZE,
    
    EVE_RIGHT=KEY_RIGHT,
    EVE_LEFT=KEY_LEFT,
    EVE_UP=KEY_UP,
    EVE_DOWN=KEY_DOWN,
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

  typedef struct{
    unsigned char red;
    unsigned char blue;
    unsigned char green;
  }RGB;

  typedef WINDOW* WinPtr;
  typedef std::ifstream File;
  typedef std::wifstream WFile;
}

