#include "Scene.hpp"
#include "Textures.hpp"
#include "scgb.hpp"

namespace Invader{
  class TitleScene:public Scene{
  private:
    scgb::Boundary boundary;
    // AAtexts
    scgb::AAtext titlelogo;
    scgb::AAtext invader1;
    scgb::AAtext invader2;
    scgb::AAtext invader3;
    scgb::AAtext ufo;
    scgb::Rectangle base;
    scgb::Text one;
    scgb::Text two;
    scgb::Text three;
    scgb::Text four;
    scgb::Text pressanybutton;
  public:
    void Draw(){
      base.Draw();
      titlelogo.Draw();
      invader1.Draw();
      invader2.Draw();
      invader3.Draw();
      ufo.Draw();
      one.Draw();
      two.Draw();
      three.Draw();
      four.Draw();
      pressanybutton.Draw();
    }
    
    TitleScene(Textures &textures):boundary(0,0,200,50){
      base.SetSize(200,50);
      base.SetBorder(true);
      titlelogo.SetOrigin(50,5);
      titlelogo.SetAAfile(textures["TitleLogo"]);
      invader1.SetAAfile(textures["Invader1"]);
      invader1.SetOrigin(70,20);
      invader2.SetAAfile(textures["Invader2"]);
      invader2.SetOrigin(70,25);
      invader3.SetAAfile(textures["Invader3"]);
      invader3.SetOrigin(70,30);
      ufo.SetAAfile(textures["UFO"]);
      ufo.SetOrigin(70,35);
      one.SetText(L"10 Point");
      one.SetOrigin(85,21);
      two.SetText(L"20 Point");
      two.SetOrigin(85,26);
      three.SetText(L"30 Point");
      three.SetOrigin(85,31);
      four.SetText(L"??? Point");
      four.SetOrigin(85,36);
      pressanybutton.SetText(L"Press 's' to start");
      pressanybutton.SetOrigin(70,41);
    }
  };
}
