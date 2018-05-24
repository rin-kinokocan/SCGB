#include "class/WindowContainer.h"
using namespace scgb;

void WindowContainer::Refresh(){
  for(auto& i:drawentity){   
    i.second->Refresh();
  }
}
