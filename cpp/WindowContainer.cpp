#include "class/WindowContainer.h"
using namespace std;
using namespace scgb;

void WindowContainer::Refresh(){
  for(auto& i:drawentity){   
    i.second->Refresh();
  }
}

void WindowContainer::Resize(){
  for(auto& i:drawentity){
    i.second->Resize();
    i.second->Refresh();
  }
}

void WindowContainer::Draw(){
  for(auto i:drawentity){
    i.second->Draw();
    i.second->DrawOnScreen();
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
  isHidden=true;
  for(auto a:drawentity){
    auto b=dynamic_pointer_cast<Drawable>(a.second);
    b->Show();
  }
}
