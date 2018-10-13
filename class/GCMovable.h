#include "GameObject.hpp"

namespace scgb{
  class GOMovable:public GameObject{
  public:
    virtual void Exec(InputMap im){
      if(im->GetBool(SCGB_LEFT))
	wpd->Move(Left);
      if(im->GetBool(SCGB_RIGHT))
	wpd->Move(Right);
      if(im->GetBool(SCGB_UP))
	wpd->Move(Up);
      if(im->GetBool(SCGB_DOWN))
	wpd->Move(Down);
    }
    GCMovable(WeakPtr<Drawable> pwpd)
      :GameComponent(pwpd){}
  };
}
