#include "InputBox.hpp"
#include "Color.hpp"
#include "Border.hpp"
#include "TextWriter.hpp"
#include "Cursor.hpp"

using namespace scgb;

InputBox::InputBox(attr_t attr,int maxchar,int x,int y,int w,int h):WindowContainer(x,y){
  this->maxchar=maxchar;
  RGBvalue block(120,120,120);
  RGBvalue cursor(0,0,0);
  AddDC(0,new Border(attr,w,h));
  AddDC(1,new TextWriter(attr,w-2,h-1),1,1);
  AddDC(2,new Block(Color::GetByBackGround(block),maxchar,1),1,2);
  AddDC(3,new Cursor(Color::GetByBackGround(cursor)),1,2);
}

void InputBox::ChangeTitle(std::wstring title){
  auto tw=GetDC<TextWriter>(1);
  tw->ChangeText(title);
}
void InputBox::StartInput(){
  isStarted=true;
}
std::wstring InputBox::GetInput(int maxch){
  return input;
}

void InputBox::Exec(InputMap im){
  if(isStarted==false)
    return;
  
}
