#include "WindowContainer.h"
using namespace std;
using namespace scgb;

void WindowContainer::Draw(){
  if(!isHidden){
    for(auto i:drawlist){
      i.second->Draw();
    }
  }
}
  
void WindowContainer::Hide(){
  isHidden=true;
  for(auto i:drawlist){
    i.second->Hide();
  }
}

void WindowContainer::Show(){
  isHidden=false;
  for(auto i:drawlist){
    i.second->Show();
  }
}

void WindowContainer::DeleteDrawable(int l){
  auto a=drawlist.find(l);
  if(a!=drawlist.end()){
    drawlist.erase(a);
  }
}

WindowContainer::WindowContainer
(double x,double y,int w,int h)
  :DrawingComponent(x,y,w,h){};
