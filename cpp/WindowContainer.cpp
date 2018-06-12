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
  for(auto i:drawentity){
    i.second->Draw();
    i.second->DrawOnScreen();
  }
}

void WindowContainer::DrawOnScreen(){
  for(auto i:drawentity){
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

void WindowContainer::DeleteDrawable(int l){
  auto a=drawentity.find(l);
  if(a!=drawentity.end()){
    drawentity.erase(a);
  }
}

Vector2D WindowContainer::GetMaxXY(){
  Vector2D v,a;
  a=Util::GetMaxScrXY();
  int c=x+width,d=y+height;
  v.resize(2);
  v[0]=max(a[0],c);v[1]=max(a[1],c);
  return v;
}

cChar WindowContainer::GetWholeScreen(int x,int y){
  return parentcontainer->GetWholeScreen(x,y);
}

void WindowContainer::AddWholeScreen(int x,int y,cChar c){
  parentcontainer->AddWholeScreen(x,y,c);
}
