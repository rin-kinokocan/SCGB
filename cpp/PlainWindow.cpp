#include "PlainWindow.h"
using namespace scgb;
using namespace scgb::Util;

void PlainWindow::Draw(){
};

PlainWindow::PlainWindow(int x,int y,int w,int h,chtype CP):
  BaseWindow(x,y,w,h){
  ColorPair=CP;
}
