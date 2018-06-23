#include <cstdlib>
#include <unistd.h>
#include "../include/scgb.h"
using namespace scgb;

int main(){
  Screen scr;
  scr.Init();
  BMimageBuilder kinoko(20,0,"./assets/kinoko.bmp");
  AAtextBuilder ebi(20,0,"./assets/ebi.aa");
  IBBuilder ib(10,0,20,10,"Input Your Name");
  scr.AddDrawable<BMimage>(1,&kinoko);
  auto test=scr.AddDrawable<AAtext>(2,&ebi);
  auto input=scr.AddDrawable<InputBox>(3,&ib);

  endwin();
  return 0;
}

