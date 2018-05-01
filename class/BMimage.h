#pragma once
#include <ncurses.h>
#include <vector>
#include "Movable.hh"
 
namespace scgb{
  class BMimage :public Movable{
  protected:
    void ReadFile();
    File file;
    BMfile bf;
    BMinfo bi;
    std::vector<int> Pixels;
  public:
    void Draw();
    void Refresh();
    BMimage(int x,int y,const char* filename);
    ~BMimage();
  };
}
