#include "class/InputBox.h"
#include "include/scgb.h"
using namespace std;
using namespace scgb;

void InputBox::Draw(){
  if(isActive){
    WindowContainer::Draw();
  }
}

std::vector<wchar_t> InputBox::GetInput(){
  auto a=dynamic_pointer_cast<UserInput>(drawentity.at(1));
  a->WaitInput(maxchar,false);
  return a->GetData();    
}

InputBox::InputBox(int x,int y,int w,int h,int mc,string display)
{
  maxchar=mc;
  info=display;
  this->x=x;this->y=y;
  this->w=w;this->h=h;
  AddDrawable<PlainWindow>(0,new PlainWindow(x,y,w,h,COLOR_PAIR(5),true));
  AddDrawable<UserInput>(1,new UserInput(x+1,y+3,w-1,1));
  for(auto a:drawentity){
    auto b=dynamic_pointer_cast<BaseWindow>(a.second);
    b->Hide();
  }
}

void InputBox::SetActive(bool b){
  isActive=b;
  for(auto a:drawentity){
    auto b=dynamic_pointer_cast<BaseWindow>(a.second);
    b->Show();
  }
}
