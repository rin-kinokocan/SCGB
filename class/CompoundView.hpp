#pragma once
#include "BaseView.hpp"

namespace scgb{
  class CompoundView:public BaseView{
  public:
    void Draw(){
      for(auto &i:views){
	i->Draw();
      }
    }

    WindowInfo CreateSubWI(Boundary *bound,Coordinate *ori){
      return WindowInfo(wi,bound,ori);
    }
    CompoundView(WindowInfo wi)
      :BaseView(wi){}
  protected:
    std::vector<std::unique_ptr<BaseView>> views;
  };
}
