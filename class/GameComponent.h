#pragma once
#include "GameObject.h"

namespace scgb{
  
  class GameComponent:public GameObject{
  protected:
    WeakPtr<Drawable> wpd;
    InputMap* im;
  public:
    virtual void Draw(){wpd->Draw();};
    GameComponent(WeakPtr<Drawable> pwpd,InputMap* pim)
      :wpd(pwpd),im(pim){}
  };

  class GCBuilder{
  protected:
    DrawableBuilder* db;
    WeakPtr<Drawable> wpd;
    InputMap* im;
  public:
    virtual GameComponent* GetResult()=0;
    void SetDrawable(WeakPtr<Drawable> pwpd){
      wpd=pwpd;
    }
    void SetIM(InputMap* pim){
      im=pim;
    }
    DrawableBuilder* GetDrawableBuilder(){
      return db;
    }
    GCBuilder(DrawableBuilder* pdb){db=pdb;}
  };
}
