#pragma once
#include <memory>
#include "Scene.hpp"

namespace scgb{
  class GameContext{
  protected:
    std::shared_ptr<Scene> scene;
  public:
    template <class T> std::shared_ptr<T> ChangeScene(T&& s){
      scene=std::make_shared<T>(std::move(s));
      return scene;
    }
    void Draw(){
      scene->Draw();
    }
  };
}
