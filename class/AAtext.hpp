#pragma once
#include "BaseWindow.hpp"

namespace scgb{
  class AAtext :public BaseWindow{
    // Draws Ascii Art (with Unicode chars).
    // Model prefix:AA
  public:
    void Draw();
  };
}
