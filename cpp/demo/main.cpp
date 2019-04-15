#include "scgb.hpp"
using namespace scgb;
using namespace scgb::Util;

class TestScene{
private:
  Rectangle rect;
  Text text;
  AAtext aa;
  AAfile roflcopter;
public:
  TestScene(){
    rect.SetOrigin(8,8);
    rect.SetSize(15,15);
    text.SetText(L"Hay, I changed something! You can't see it though!");
    text.SetOrigin(10,10);
    roflcopter.SetFile("../assets/Logo.aa");
    aa.SetAAfile(roflcopter);
    aa.SetOrigin(10,11);
  }
  void Draw(){
    rect.Draw();
    text.Draw();
    aa.Draw();
  }
};


int main(){
  Root system;
  TestScene ts;
  InputMap im;
  Clock clock;
  system.Init();
  while(!system.IsEnd()){
    system.Delete();
    ts.Draw();
    system.Update(im);
    clock.WaitFrame();
  }
  system.End();
  return 0;
}
