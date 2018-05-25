#include "class/Color.hh"
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
  else
    delta=255/2+1;
  if(!can_change_color()){
    for(int i=1;i<=COLORS;i++){
      init_pair(i,0,i);
    }
    return;
  }
  int p=1;
  for(int r=0;r<=255;r+=delta)
    for(int g=0;g<=255;g+=delta)
      for(int b=0;b<=255;b+=delta)
	init_color(p++,r/255.0*1000,g/255.0*1000,b/255.0*1000);
  for(int i=1;i<=COLORS;i++){
    init_pair(i,0,i);
  }
}

int Color::GetColor(unsigned char r,unsigned char  g,unsigned char  b){
  if(!has_colors()){
    return 0;
  }
  else if(can_change_color())
    return (r*pow(phase,2)+g*phase+b)/delta+1;
  else{
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
}

