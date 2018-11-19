#include "BaseWindow.hpp"
namespace scgb{
  class TextWriter:public BaseWindow{
  protected:
    std::wstring text;
    attr_t attr;
  public:
    void Draw(int x,int y){
      InitDraw(x,y);
      AddStr(text.c_str(),attr);
    }
    void ChangeText(std::wstring str){
      text=str;
    }
    TextWriter(attr_t a,int w,int h):BaseWindow(w,h){
      attr=a;
    }
  };
}
