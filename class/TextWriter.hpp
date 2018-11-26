#include "Block.hpp"
namespace scgb{
  class TextWriter:public Block{
  protected:
    std::wstring text;
  public:
    void Draw(int x,int y){
      InitDraw(x,y);
      AddStr(text.c_str(),attr);
    }
    void ChangeText(std::wstring str){
      text=str;
    }
    TextWriter(attr_t a,int w,int h):Block(a,w,h){}
  };
}
