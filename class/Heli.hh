#include "./AAtext.h"

namespace scgb{
  class Heli:public AAtext{
  public:
    Heli():AAtext(10,10,"./assets/roflcopter.aa"){};
    void MOVE(Direction);
  };
}
