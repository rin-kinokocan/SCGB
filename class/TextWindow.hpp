#include "WindowContainer.hpp"
#include "Border.hpp"
#include "DrawText.hpp"
namespace scgb{
  class TextWindow:public WindowContainer{
  public:
    TextWindow(attr_t a,int w,int h):WindowContainer(w,h){
      AddDrawable(0,new Border(a,w,h));
      AddDrawable(1,new DrawText(a,w,h));
    }
    void ChangeText(std::wstring str){
      auto dt=GetDrawable<DrawText>(1);
      dt->ChangeText(str);
    }
  };
}
