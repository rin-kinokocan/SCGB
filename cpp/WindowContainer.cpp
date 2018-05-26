#include "class/WindowContainer.h"
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
