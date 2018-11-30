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
  LoadPalette("assets/default.pal");
  return true;
}

attr_t Color::GetColorPair(RGBvalue front,RGBvalue back){
  //Get pair of closest colors from given rgb values.
  //If the color pair is not available, create new one.
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
  else
    throw std::runtime_error("Too much color pairs required.");
  return COLOR_PAIR(colorpairs);
}

attr_t Color::GetByBackGround(RGBvalue rgb){
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
  if(colorpairs<COLOR_PAIRS-1){
    colorpairs++;
    init_pair(colorpairs,0,b);
  }
  else
    throw std::runtime_error("Too much color pairs required.");
  return COLOR_PAIR(colorpairs);
}

  
static inline short CalcRgb(short x){
  return (short)(x/1000.0*255);
}

static inline int CalcDiff(RGBvalue rgb1,RGBvalue rgb2){
  int r=(rgb1[0]+rgb2[0])/2;
  int dr=pow(rgb1[0]-rgb2[0],2);
  int dg=pow(rgb1[1]-rgb2[1],2);
  int db=pow(rgb1[2]-rgb2[2],2);
  return 2*dr+4*dg+3*db+r*(dr-db)/256;
}

short Color::GetColor(RGBvalue rgb){
  //Get closest color from given rgb value.
  //Result will change when you use custom palettes.
  //rgb values:0~255
  if(!has_colors())
    return 0;
  RGBvalue rgb2;
  int dif,dif2;
  short res;
  for(int i=0;i<COLORS;i++){
    color_content(i,&rgb2[0],&rgb2[1],&rgb2[2]);
    rgb2[0]=CalcRgb(rgb2[0]);
    rgb2[1]=CalcRgb(rgb2[1]);
    rgb2[2]=CalcRgb(rgb2[2]);
    dif2=CalcDiff(rgb,rgb2);
    if(i==0 || dif>dif2){
      res=i;
      dif=dif2;
    }
  }
  color_content(res,&rgb2[0],&rgb2[1],&rgb2[2]);
  rgb2[0]=CalcRgb(rgb2[0]);
  rgb2[1]=CalcRgb(rgb2[1]);
  rgb2[2]=CalcRgb(rgb2[2]);
  return res;
}

void Color::LoadPalette(std::string filename){
  /*
    I assume that default curses color macros
    (COLOR_BLACK to COLOR_WHITE) are 0~7.
    At least, ncurses and PDcurses are using these numbers.
  */
  if(COLORS<=8)
    return;
  std::ifstream file(filename);
  if(!file.is_open())
    throw std::runtime_error("cannot open a pallete file");
  std::string dat;
  int r,g,b;
  for(int i=8;i<COLORS;i++){
    if(file.eof())
      break;
    try{
      std::getline(file,dat,' ');
      r=std::stoi(dat);
      std::getline(file,dat,' ');
      g=std::stoi(dat);
      std::getline(file,dat,'\n');
      b=std::stoi(dat);
      init_color(i,r,g,b);
    }
    catch(std::invalid_argument e){
      break;
    }
  }
}
