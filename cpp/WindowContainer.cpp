#include "class/WindowContainer.h"
using namespace std;
using namespace scgb;

void WindowContainer::Refresh(){
  for(auto& i:drawentity){   
    i.second->Refresh();
  }
}

void WindowContainer::OnResize(){
  for(auto& i:drawentity){
    i.second->OnResize();
    i.second->Refresh();
  }
}

void WindowContainer::Draw(){
  if(!isHidden){
    for(auto i:drawentity){
      i.second->Draw();
    }
  }
}
  
void WindowContainer::Hide(){
  isHidden=true;
  for(auto a:drawentity){
    auto b=dynamic_pointer_cast<Drawable>(a.second);
    b->Hide();
  }
}

void WindowContainer::Show(){
  isHidden=false;
  for(auto a:drawentity){
    auto b=dynamic_pointer_cast<Drawable>(a.second);
    b->Show();
  }
}

void WindowContainer::DeleteDrawable(int l){
  auto a=drawentity.find(l);
  if(a!=drawentity.end()){
    drawentity.erase(a);
  }
}

WindowContainer::WindowContainer
(int x,int y,int w,int h,SizeData* psd,SizeData sd)
  :Drawable(x,y,w,h,psd){};

WindowContainer::WindowContainer
(int x,int y,int w,int h,SizeData* psd)
  :Drawable(x,y,w,h,psd){};
