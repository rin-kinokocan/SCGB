#pragma once
#include "CompoundView.hpp"
#include "Block.hpp"
#include "Text.hpp"

namespace scgb{
  class TextBox:public CompoundView{
  public:
    TextBox(WindowInfo wi,std::shared_ptr<Attribute> attr,std::shared_ptr<String> str)
     :CompoundView(wi){
      auto geo=wi.geometry->GetData();
      auto block_wi=CreateSubWI(new Geometry(geo[0],geo[1]),new Coordinate(0,0));
      auto text_wi=CreateSubWI(new Geometry(geo[0]-4,geo[1]-2),new Coordinate(2,1));
      views.push_back(std::make_unique<Block>(block_wi,attr));
      views.push_back(std::make_unique<Text>(text_wi,attr,str));
    }
  };
}
