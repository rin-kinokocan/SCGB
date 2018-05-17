#include "define.h"
#include "Movable.hh"

namespace scgb{
  class UserInput :public Movable{
  protected:
    std::vector<wchar_t> data;
  public:
    void Draw();
    void WaitInput(int maxChar);
     UserInput(int,int,int,int);
    ~UserInput();
  };
}

