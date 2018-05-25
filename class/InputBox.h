#include "define.h"
#include "WindowContainer.h"

namespace scgb{
  class InputBox:public WindowContainer{
  public:
    std::string info;
    void Draw();
    InputBox(int x,int y,int width,int height,int maxchar,std::string);
  };
}
