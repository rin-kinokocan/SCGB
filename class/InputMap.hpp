#pragma once
#include <string>
#include <map>
#include <curses.h>

namespace scgb{
  class InputMap{
  private:
    std::map<wint_t,bool> map;
    std::wstring input;
  public:
    void Update();
    bool GetBool(wint_t k);
    std::wstring GetInput(){
      return input;
    }
  };
}
