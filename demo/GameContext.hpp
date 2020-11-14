#pragma once
#include <memory>
#include "Scene.hpp"

namespace scgb{
  class GameContext{
  protected:
    std::shared_ptr<Scene> scene;
    bool isend=false;
  public:
    template <class T> std::shared_ptr<Scene> ChangeScene(std::shared_ptr<T> s){
      scene=s;
      return scene;
    }
    void Draw(){
      scene->Draw();
    }
    void Update(){
      scene->Update();
    }
    void HandleInput(wint_t in,int code){
      scene->HandleInput(*this,in,code);
    }
    void EndGame(){
      isend=true;
    }
    bool IsEnd(){
      return isend;
    }
  };
}
