#pragma once
#include "BaseWindow.h"
#include "Movable.hh"

namespace scgb{
  class AAtext :public Movable{
  protected:
    WFile file;
  public:
    void Draw();
    void Refresh();
    void Resize();
    void DrawTransparent(int w);
    int DrawPolicy(int,int,int);
    AAtext(int x,int y,std::string filename);
    ~AAtext();
  };
}
