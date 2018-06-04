#pragma once
#include "Movable.hh"

namespace scgb{
  class UserInput :public Movable{
  protected:
    std::vector<wchar_t> data;
    virtual wchar_t GetInput(){
      wint_t tmp;wget_wch(window,&tmp);
      return tmp;
    };
    void WindowSetting();
  public:
    void Draw();
    void WaitInput(int maxChar,bool isblankok=true);
    std::vector<wchar_t> GetData();
    UserInput(int,int,int,int);
    ~UserInput();
  };
}

