#include "WindowContainer.hpp"
using namespace std;
using namespace scgb;

void WindowContainer::Draw(int x,int y){
    for(auto i:drawlist){
      i.second->Draw(x,y);
    }
}

void WindowContainer::DeleteDrawable(int l){
  auto a=drawlist.find(l);
  if(a!=drawlist.end()){
    drawlist.erase(a);
  }
}
