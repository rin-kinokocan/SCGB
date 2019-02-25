#include "Color.hpp"
#include <cmath>
#include <unistd.h>

using namespace scgb;

int Color::colorpairs=0;
bool Color::Init(){
  //initializes colors
  if(!has_colors())
    return false;
  start_color();
  SetColors();
  return true;
}

attr_t Color::GetColorPair(RGBvalue& front,RGBvalue& back){
  /*
    Get pair of closest colors from given rgb values.
    If there is no such color pair, it will create new one.
  */
  if(!has_colors())
    return 0;
  auto f=GetColor(front);
  auto b=GetColor(back);
  short pf,pb;
  for(int i=1;i<colorpairs;i++){
    pair_content(i,&pf,&pb);
    if(pb==b && pf==f){
      return COLOR_PAIR(i);
    }
  }
  if(colorpairs<COLOR_PAIRS-1){
    colorpairs++;
    init_pair(colorpairs,f,b);
  }
  else{
    throw std::runtime_error("Over "+std::to_string(COLOR_PAIRS)+" color pairs required.");
  }
  return COLOR_PAIR(colorpairs);
}

attr_t Color::GetByBackGround(RGBvalue& rgb){
  if(!has_colors())
    return 0;
  auto b=GetColor(rgb);
  short pf,pb;
  for(int i=1;i<colorpairs;i++){
    pair_content(i,&pf,&pb);
    if(pb==b){
      return COLOR_PAIR(i);
    }
  }
  RGBvalue black(255,255,255);
  return GetColorPair(black,rgb);
}

attr_t Color::GetByForeGround(RGBvalue& rgb){
  if(!has_colors())
    return 0;
  auto b=GetColor(rgb);
  short pf,pb;
  for(int i=1;i<colorpairs;i++){
    pair_content(i,&pf,&pb);
    if(pf==b){
      return COLOR_PAIR(i);
    }
  }
  RGBvalue black(255,255,255);
  return GetColorPair(black,rgb);
}
  
static inline short CalcRgb(short x){
  return (short)(x/1000.0*255);
}

static inline int CalcDiff(RGBvalue& rgb1,RGBvalue& rgb2){
  int r=(rgb1[0]+rgb2[0])/2;
  int dr=pow(rgb1[0]-rgb2[0],2);
  int dg=pow(rgb1[1]-rgb2[1],2);
  int db=pow(rgb1[2]-rgb2[2],2);
  return 2*dr+4*dg+3*db+r*(dr-db)/256;
}

short Color::GetColor(RGBvalue& rgb){
  //Get closest color from given rgb value.
  //rgb values:0~255
  if(!has_colors())
    return 0;
  RGBvalue rgb2;
  int dif,dif2,i=8;
  short res=0;
  for(int r=0;r<=255;r+=51){
    for(int g=0;g<=255;g+=51){
      for(int b=0;b<=255;b+=51){
	rgb2[0]=r;
	rgb2[1]=g;
	rgb2[2]=b;
	dif2=CalcDiff(rgb,rgb2);
	if(i==8 || dif>dif2){
	  res=i;
	  dif=dif2;
	}
	i++;
      }
    }
  }
  return res;
}

static inline int conv(int x){
  return x*1000/255.0;
}

void Color::SetColors(){
  /*
    I assume that default curses color macros
    (COLOR_BLACK to COLOR_WHITE) are 0~7.
    At least, ncurses and PDcurses are using these numbers.

    With PDCurses on Windows, init_color() cannot change
    more than 16 color definitions.
    However, the default pallete is exactly the same
    thing as the original colors set on initialization.
    Hence you don't need to worry about colors
    if you stick with the normal 256 colors.

    After all, this function just gives ncurses 
    the default color definitions which should be used on
    color_content().
   */
  int i=8;
  if(COLORS<256 || !can_change_color())
    return;
  for(int r=0;r<=255;r+=51){
    for(int g=0;g<=255;g+=51){
      for(int b=0;b<=255;b+=51){
	init_color(i,conv(r),conv(g),conv(b));
	i++;
      }
    }
  }
}

