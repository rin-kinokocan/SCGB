#include "BaseWindow.hpp"

namespace scgb{
  class Border:public BaseWindow{
  protected:
    attr_t attr;
  public:
    void Draw(int x,int y){
      InitDraw(x,y);
      AddChar(L'┌',attr);
      for(int i=0;i<width-2;i++){
	AddChar(L'─',attr);
      }
      AddChar(L'┐',attr);
      for(int i=0;i<height-2;i++){
	AddChar(L'│',attr);
	for(int j=0;j<width-2;j++)
	  AddChar(L' ',attr);
	AddChar(L'│',attr);
      }
      AddChar(L'└',attr);
      for(int i=0;i<width-2;i++){
	AddChar(L'─',attr);
      }
      AddChar(L'┘',attr);
    }
    Border(attr_t a,int w,int h):BaseWindow(w,h){attr=a;}
  };
}
