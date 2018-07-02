#include "GameComponent.h"

namespace scgb{
  class GCMovable:public GameComponent{
  public:
    virtual void Exec(){
    }
    GCMovable(WeakPtr<Drawable> pwpd,InputMap* pim)
      :GameComponent(pwpd,pim){}
  };
  
  class GCMovableBuilder:public GCBuilder{
  public:
    GameComponent* GetResult(){
      return new GCMovable(wpd,im);
    }
    GCMovableBuilder(DrawableBuilder* pdb):GCBuilder(pdb){}
  };
}
