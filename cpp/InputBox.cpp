#include "class/InputBox.h"
#include "include/scgb.h"
using namespace std;
using namespace scgb;

void InputBox::Draw(){
  WindowContainer::Draw();
  auto a=dynamic_pointer_cast<BaseWindow>(drawentity.at(0));
  a->AddStr(info,1,1);
}

// std::vector<wchar_t> InputBox::GetInput(){
//   Show();
//   auto a=dynamic_pointer_cast<UserInput>(drawentity.at(1));
//   a->WaitInput(maxchar,false);
//   Hide();
//   return a->GetData();
// }

InputBox::InputBox(int x,int y,int w,int h,SizeData* psd,string display)
  :WindowContainer(x,y,w,h,psd){
  for(auto a:display){
    info.push_back(Util::make_cChar(a,0));
  }
  PWBuilder pw(x,y,w,h);
  pw.SetColor(COLOR_PAIR(5)).SetBox(true);
  AddDrawable<PlainWindow>(0,&pw);
  Hide();
}
