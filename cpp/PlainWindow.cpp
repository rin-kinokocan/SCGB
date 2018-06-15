#include "class/PlainWindow.h"
using namespace scgb;
using namespace scgb::Util;

void PlainWindow::Draw(){
  InitDraw();
  if(isBox)
    box(window,ACS_VLINE,ACS_HLINE);
  wbkgd(window,ColorPair);
};

PlainWindow::PlainWindow(int x,int y,int w,int h,chtype CP,bool isBox):
  BaseWindow(x,y,w,h){
  ColorPair=CP;
  this->isBox=isBox;
}
