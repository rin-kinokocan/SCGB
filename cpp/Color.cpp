#include "../class/Color.hh"
#include <unistd.h>

using namespace scgb;

Color::Color(){
  int p=1;  
  for(int r=0;r<=255;r+=51)
    for(int g=0;g<=255;g+=51)
      for(int b=0;b<=255;b+=51)
	init_color(p++,r/255.0*1000,g/255.0*1000,b/255.0*1000);
  for(int i=1;i<COLORS;i++){
    init_pair(i,0,i);
  }
}

int Color::GetWebSafeColor(unsigned char r,unsigned char  g,unsigned char  b){
  r/=51;g/=51;b/=51;
  return r*36+g*6+b+1;
}

