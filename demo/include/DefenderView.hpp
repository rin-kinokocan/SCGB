#pragma once
#include "AAtext.hpp"
namespace Invader{
  class DefenderView{
  private:
    Defender* defender;
    scgb::AAtext defenderAA;
  public:
    void Draw(){
      defenderAA.SetOrigin(defender->GetPosition());
      defenderAA.Draw();
    }
    DefenderView(Textures& t,Defender& d){
      defender=&d;
      defenderAA.SetAAfile(t["Defender"]);
    }
  };
}
