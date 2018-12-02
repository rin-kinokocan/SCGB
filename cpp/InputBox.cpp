#include "InputBox.hpp"
#include "Color.hpp"
#include "Border.hpp"
#include "TextWriter.hpp"
#include "Cursor.hpp"

using namespace scgb;

InputBox::InputBox(attr_t attr,int maxchar,int x,int y,int w,int h):WindowContainer(x,y){
  this->maxchar=maxchar;
  RGBvalue block(120,120,120);
  RGBvalue cursor(255,255,255);
  AttachDC(0,new Border(attr,w,h));
  AttachDC(1,new TextWriter(attr,w-2,h-1),1,1);
  AttachDC(2,new Block(Color::GetByBackGround(block),maxchar*2,1),1,2);
  AttachDC(3,new TextWriter(Color::GetColorPair(cursor,block),maxchar*2,1),1,2);
  AttachDC(4,new Cursor(Color::GetByBackGround(cursor)),1,2);
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
  auto tw=GetDC<TextWriter>(3);
  auto cur=GetDC<Cursor>(4);
  if(im.GetBool(10)){
    SendMessage(EVE_ENDINPUT);
    isStarted=false;
    DeleteDC(4);
    return;
  }
  if(im.GetBool(KEY_LEFT)){
    cur->Reset();
    if(cursorpos>0)cursorpos--;
  }
  if(im.GetBool(KEY_RIGHT)){
    cur->Reset();
    if(cursorpos<maxchar-1
       && cursorpos<charnum)cursorpos++;
  }
  if(im.GetBool(KEY_DC)){
    if(cursorpos<charnum){
      input.erase(input.begin()+cursorpos);
      charnum--;
      if(cursorpos>=charnum)
	cursorpos=charnum;
    }
  }
  if(im.GetBool(127)){
    if(cursorpos>0){
      input.erase(input.begin()+cursorpos-1);
      cursorpos--;
      charnum--;
    }
  }
  
  auto in=im.GetInput();
  if(charnum+1<maxchar && in!=0){
    input.insert(cursorpos,1,in);
    charnum++;
    cursorpos++;
  }
  auto w=mk_wcswidth(input.c_str(),cursorpos);
  MoveDC(4,1+w,2);
  tw->ChangeText(input);
}
