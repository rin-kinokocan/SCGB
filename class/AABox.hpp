#pragma once
#include "CompositeDrawingComponent.hpp"
#include "AAfile.hpp"
#include "TextBox.hpp"
namespace scgb{
  class AABox :public CompositeDrawingComponent{
    // Draws things in datafile (with Unicode chars).
  public:
    AABox(const std::wstring& f,int x=0,int y=0,int w=0,int h=0):CompositeDrawingComponent(x,y,w,h){
      Add(TextBox<const std::wstring&>(f,x,y,w,h));
    }
    AABox(AAfile& f,int x=0,int y=0):CompositeDrawingComponent(x,y){
      auto size=f.GetSize();
      Add(TextBox<const std::wstring&>(f.GetData(),x,y,size[0],size[1]));
    }
    AABox(std::string&& f,int x=0,int y=0):CompositeDrawingComponent(x,y){
      // Open file and read thing.
      AAfile aaf(std::move(f));
      auto size=aaf.GetSize();
      Add(TextBox<std::wstring>(aaf.GetData(),x,y,size[0],size[1]));
    }
  };
}
