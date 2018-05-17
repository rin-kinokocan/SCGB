#include "../class/UserInput.h"

using namespace scgb;
using namespace std;

void UserInput::Draw(){
  box(window,'|','-');
  // wint_t a;
  // wget_wch(window,&a);
  // endwin();
  // wcout<<a<<endl;
  // initscr();
}

UserInput::UserInput(int x,int y,int w,int h)
  :Movable(x,y,w,h)
{
  // nodelay(window,false);
}
