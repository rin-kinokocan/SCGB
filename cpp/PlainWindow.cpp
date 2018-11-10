#include "PlainWindow.h"
using namespace scgb;
using namespace scgb::Util;

void PlainWindow::Draw(){
};

PlainWindow::PlainWindow(int w,int h,chtype CP):
  BaseWindow(w,h){
  ColorPair=CP;
}
