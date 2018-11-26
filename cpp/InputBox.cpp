#include "InputBox.hpp"
#include "Border.hpp"
#include "TextWriter.hpp"

using namespace scgb;

InputBox::InputBox(attr_t attr,int x,int y,int w,int h):WindowContainer(x,y){
  AddDC(0,new Border(attr,w,h));
  AddDC(1,new TextWriter(attr,w-2,h-1),1,1);
}

void InputBox::ChangeTitle(std::wstring title){
  auto tw=GetDC<TextWriter>(1);
  tw->ChangeText(title);
}

std::wstring InputBox::GetInput(int maxch){
  return input;
}
