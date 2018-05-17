#include "../class/UserInput.h"

using namespace scgb;
using namespace std;

void UserInput::Draw(){
  box(window,'|','-');

  wmove(window,1,1);
  for(auto c:data){
    cChar d;d.chars[0]=c;d.chars[1]='\0';
    AddChar(d);
  }
}

void UserInput::WaitInput(int maxChar){
  wint_t* a;
  a=new wint_t[maxChar];
  echo();
  nodelay(window,true);
  wgetn_wstr(window,a,maxChar);
  for(int i=0;i<maxChar;i++){
    data.push_back(a[i]);
  }
  delete(a);
}

UserInput::UserInput(int x,int y,int w,int h)
  :Movable(x,y,w,h)
{}

UserInput::~UserInput(){
  endwin();
  wcout<<"did this"<<endl;
  for(auto c:data){
    wcout<<c<<endl;
  }
}
