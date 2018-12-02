#include "SingleHandler.hpp"

namespace scgb{
  class MoveByInput :public SingleHandler{
  public:
    void Exec(InputMap im){
      if(im.GetBool(KEY_RIGHT))
	Move(Right);
      if(im.GetBool(KEY_LEFT))
	Move(Left);
      if(im.GetBool(KEY_UP))
	Move(Up);
      if(im.GetBool(KEY_DOWN))
	Move(Down);
    }
    MoveByInput(double x,double y):SingleHandler(x,y){};
  };
}
