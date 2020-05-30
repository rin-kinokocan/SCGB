#pragma once
#include "Scene.hpp"
#include <vector>
#include <memory>

namespace Invader{
  class SceneManager{
  private:
    std::vector<std::unique_ptr<Scene>> scenes;
  public:
    void Push(std::unique_ptr<Scene> s){
      scenes.push_back(std::move(s));
    }
    void Pop(){
      scenes.pop_back();
    }
    void Draw(){
      scenes.back()->Draw();
    }
  };
}
