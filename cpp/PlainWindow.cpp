#include "PlainWindow.h"
using namespace scgb;
using namespace scgb::Util;

void PlainWindow::Draw(){
};

void PlainWindow::WindowSetting(){
  if(isBox);
  // box(window,ACS_VLINE,ACS_HLINE);
  // wbkgd(window,ColorPair);
}

PlainWindow::PlainWindow(int x,int y,int w,int h,SizeData* psd,chtype CP,bool isBox):
  BaseWindow(x,y,w,h,psd){
  ColorPair=CP;
  this->isBox=isBox;
}
