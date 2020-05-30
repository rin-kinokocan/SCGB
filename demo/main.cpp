#include "scgb.hpp"
#include "Textures.hpp"
#include "TitleScene.hpp"
#include "TitleController.hpp"
#include "ControllerManager.hpp"
#include "SceneManager.hpp"

using namespace scgb;
using namespace scgb::Util;
using namespace Invader;

Textures LoadTexture(){
  Textures t;
  t.Set("TitleLogo","./assets/Logo.txt");
  t.Set("Invader1","./assets/invader1.txt");
  t.Set("Invader2","./assets/invader2.txt");
  t.Set("Invader3","./assets/invader3.txt");
  t.Set("UFO","./assets/ufo.txt");
  t.Set("Defender","./assets/defender.txt");
  return t;
}

int main(){
  scgb::Root RenderEngine;
  Textures textures=LoadTexture();
  SceneManager sm;
  ControllerManager cm;
  scgb::InputMap im;
  scgb::Clock clock(30);
  RenderEngine.Init();
  sm.Push(std::make_unique<TitleScene>(textures));
  cm.Push(std::make_unique<TitleController>(&textures,&sm,&cm));
  while(!RenderEngine.IsEnd()){
    im.Update();
    RenderEngine.Delete();
    cm.Update(im,clock.GetDeltaTime());
    sm.Draw();
    RenderEngine.Update(im);
    clock.WaitFrame();
  }
  RenderEngine.End();
  return 0;
}
