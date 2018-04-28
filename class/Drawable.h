#pragma once
#include <string>

namespace scgb{
  class Drawable{
  public:
    virtual void Draw()=0;
    virtual void Refresh()=0;
    virtual ~Drawable(){};
  };
  typedef std::wstring DrawString;
}

