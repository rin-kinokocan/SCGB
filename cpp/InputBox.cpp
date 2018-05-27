#include "class/InputBox.h"
#include "include/scgb.h"
using namespace std;
using namespace scgb;

void InputBox::Draw(){
  WindowContainer::Draw();
  auto a=dynamic_pointer_cast<BaseWindow>(drawentity.at(0));
  a->AddStr(info,1,1);
}

std::vector<wchar_t> InputBox::GetInput(){
  Show();
  Screen::Draw();
  Screen::Refresh();
  auto a=dynamic_pointer_cast<UserInput>(drawentity.at(1));
  a->WaitInput(maxchar,false);
  Hide();
  return a->GetData();
}

InputBox::InputBox(int x,int y,int w,int h,int mc,string display)
{
  maxchar=mc;
  for(auto a:display){
    info.push_back(Util::make_cChar(a,0));
  }
  this->x=x;this->y=y;
  this->w=w;this->h=h;
  AddDrawable<PlainWindow>(0,new PlainWindow(x,y,w,h,COLOR_PAIR(5),true));
  AddDrawable<UserInput>(1,new UserInput(x+1,y+3,w-2,1));
  Hide();
}
