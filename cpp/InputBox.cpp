#include "InputBox.h"
#include "PlainWindow.h"
using namespace std;
using namespace scgb;

void InputBox::Draw(){
  WindowContainer::Draw();
  auto a=GetDrawable<PlainWindow>(0);
  a->AddStr(info,1,1);
}


InputBox::InputBox(double x,double y,int w,int h,string display)
  :WindowContainer(x,y,w,h){
  for(auto a:display){
    info.push_back(Util::make_cChar(a,0));
  }  
  AddDrawable<PlainWindow>(0,new PlainWindow(x,y,w,h,COLOR_PAIR(5)));
  Hide();
}
