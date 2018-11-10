#pragma once
#include "WindowContainer.h"

namespace scgb{
  class InputBox:public WindowContainer{
  public:
    InputBox(int w,int h):WindowContainer(w,h){};
  };
}
