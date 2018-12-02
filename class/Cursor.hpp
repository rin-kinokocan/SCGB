#pragma once
#include "BaseWindow.hpp"
#include "Clock.hpp"

// Next subject of refactoring.
namespace scgb{
  class Cursor :public BaseWindow{
  protected:
    attr_t attr;
    wchar_t ch=L' ';
    bool toggle=false;
    int timer=0;
    int hz=1;
  public:
    void Draw(int x,int y){
      InitDraw(x,y);
      timer+=Clock::GetDeltaTime();
      if((double)timer/1000>(double)1/(2*hz)){
	toggle=!toggle;
	timer=0;
      }
      if(toggle)
	AddChar(ch,attr);
    }
    void Reset(){
      toggle=true;
      timer=0;
    }
    Cursor(attr_t attr,int hz=1,wchar_t ch=L' '):BaseWindow(1,1){
      this->attr=attr;
      this->hz=hz;
      this->ch=ch;
    };
  };
}
