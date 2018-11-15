#include "Color.hpp"
#include <cmath>
#include <iostream>
#include <exception>
using namespace scgb;
int Color::phase;
int Color::delta;

void Color::Init(){//initializes color_pairs
  
  if(!has_colors())
    return;
  start_color();
  use_default_colors();

  phase=0;
  for(int i=0;pow(i,3)<COLORS;i++){
    phase++;
  }
  phase--;
  if(phase!=1)
    delta=255/(phase-1);
  
  if(!can_change_color() || phase==1){//if cannot change colors
    //or if COLORS are smaller than 9(the default would be better).
    if(phase==1)
      delta=255/2+1;
    for(int i=1;i<=COLORS;i++){
      init_pair(i,0,i);
    }
    return;
  }
  
  int p=0;
  for(int r=0;r<=255;r+=delta)
    for(int g=0;g<=255;g+=delta)
      for(int b=0;b<=255;b+=delta)
	init_color(p++,r/255.0*1000,g/255.0*1000,b/255.0*1000);
  for(int i=1;i<=COLORS;i++){
    init_pair(i,0,i);
  }
}

int Color::GetColor(unsigned char r,unsigned char  g,unsigned char  b){
  //returns corresponding color number set by Init.
  if(!has_colors()){
    return 0;
  }
  else if(!can_change_color() ||COLORS<=8){
    r/=delta,g/=delta,b/=delta;
    for(int i=0;i<COLORS;i++){
      short ri,gi,bi;
      color_content(i,&ri,&gi,&bi);
      ri=ri/1000.0*255/delta;gi=gi/1000.0*255/delta;
      bi=bi/1000.0*255/delta;
      if(r==ri && b==bi && g==gi)
	return i;
    }
    return 0;
  }
  else{
    return (r*pow(phase,2)+g*phase+b)/delta;
  }
}

