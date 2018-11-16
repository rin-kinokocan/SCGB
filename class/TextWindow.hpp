#include "WindowContainer.hpp"
#include "Border.hpp"
#include "DrawText.hpp"
namespace scgb{
  class TextWindow:public GameObject{
  private:
    using GameObject::AttachDrawingComponent;
  public:
    TextWindow(attr_t a,int x,int y,int w,int h):GameObject(x,y){
      AttachDrawingComponent(new WindowContainer(w,h));
      auto dcp=GetDrawingComponent<WindowContainer>();
      dcp->AddDrawable(0,new Border(a,w,h));
      dcp->AddDrawable(1,new DrawText(a,w,h));
    }
    void ChangeText(std::wstring str){
      auto dcp=GetDrawingComponent<WindowContainer>();
      auto dt=dcp->GetDrawable<DrawText>(1);
      dt->ChangeText(str);
    }
  };
}
