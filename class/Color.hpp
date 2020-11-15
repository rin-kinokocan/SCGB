#pragma once
#include <curses.h>
#include <cmath>
namespace scgb{
  class Color{
    // manages color palette
    // Singleton. But I can't remember the static state it had.
  private:
    Color(){}
  public:
    Color(Color &col)=delete;
    void operator=(const Color col)=delete;
    
    static Color& GetInstance(){
      static Color instance;
      return instance;
    }
    
    attr_t GetColorPair(int r,int g,int b){
      if(!has_colors())
	return 0;
      int res=0,max=0;
      int ColMax;
      if(can_change_color())
	ColMax=1000;
      else
	ColMax=680;
      r=r*ColMax/255.0;
      g=g*ColMax/255.0;
      b=b*ColMax/255.0;
      for(int i=1;i<COLOR_PAIRS;i++){
	short pf,pb,cr,cg,cb;
	pair_content(i,&pf,&pb);
	color_content(pb,&cr,&cg,&cb);

	int dist=pow(r-cr,2)+pow(g-cg,2)+pow(b-cb,2);
	
	if(dist<max || res==0){
	  max=dist;
	  res=i;
	}
      }
      return res;
    }

    short GetColor(int r,int g,int b){
      //rgb values:0~255
      if(!has_colors())
	return 0;      
      short cr,cg,cb;
      int res=0,max=0;
      int ColMax;
      if(can_change_color())
	ColMax=1000;
      else
	ColMax=680;
      r=r*ColMax/255.0;
      g=g*ColMax/255.0;
      b=b*ColMax/255.0;
      for(int i=0;i<COLORS;i++){
	color_content(i,&cr,&cg,&cb);
	int dist=pow(r-cr,2)+pow(g-cg,2)+pow(b-cb,2);
	if(dist<max || res==0){
	  max=dist;
	  res=i;
	}
      }
      return res;
    }
  };
}
