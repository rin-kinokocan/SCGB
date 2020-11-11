#pragma once
#include <functional>
#include "CompositeDrawingComponent.hpp"
#include "Rectangle.hpp"
#include "TextBox.hpp"
namespace scgb{
  class MessageWindow :public CompositeDrawingComponent{
    // Bordered text window.
    // Wraps TextBox to handle reference better.
  public:
    MessageWindow(std::wstring& str,attr_t attr,int x=0,int y=0,int w=0,int h=0):CompositeDrawingComponent(x,y,w,h){
      Add(Rectangle(attr,x,y,w,h));
      Add(TextBox<std::wstring&>(str,x+1,y+1,w-4,h-2));
    }
    MessageWindow(std::wstring&& str,attr_t attr,int x=0,int y=0,int w=0,int h=0):CompositeDrawingComponent(x,y,w,h){
      Add(Rectangle(attr,x,y,w,h));
      Add(TextBox<std::wstring>(std::move(str),x+1,y+1,w-4,h-2));
    }
    void ChangeMessage(std::wstring& str){
      Remove();
      Add(TextBox<std::wstring&>(str,x+1,y+1,width-4,height-2));
    }
    void ChangeMessage(std::wstring&& str){
      Remove();
      Add(TextBox<std::wstring>(std::move(str),x+1,y+1,width-4,height-2));
    }

  };
}
