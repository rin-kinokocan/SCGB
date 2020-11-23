#pragma once
#include <curses.h>
#include "define.hpp"

namespace scgb{
  class DrawingComponent{
  public:
    virtual void Draw()=0;
    void Move(int dx,int dy){
      x+=dx;
      y+=dy;
    }

    void SetTransparency(bool t){
      IsTransparent=t;
    }
    
    DrawingComponent(int x=0,int y=0,int width=0,int height=0):x(x),y(y),width(width),height(height){}
  private:
    // virtual cursor position
    int curx=0;
    int cury=0;
  protected:
    // left top of the window
    int x=0;
    int y=0;
    int width=0;
    int height=0;
    // Something you can use
    bool IsTransparent=false;
    
    void AddChar(wchar_t ch,attr_t attr){
      if(ch==L'\n'||ch==L'\rn'){
	MoveCursor(0,cury+1);
      }
      else if(IsDrawable()){
	if(IsTransparent){
	  auto a=inch();
	  if(ch==L' '){
	    ch=a&(A_CHARTEXT);
	  }
	  if(attr&A_COLOR)
	    a=a&(~A_COLOR);
	  a=a&A_ATTRIBUTES;
	  attr=attr|a;
	}
	std::wstring str(1,ch);
	cchar_t c;
	setcchar(&c,str.c_str(),attr,0,nullptr);
	attron(attr);
	add_wchnstr(&c,1);
	attroff(attr);
	MoveCursor(curx+mk_wcwidth(ch),cury);
      }
    }
    
    void AddChar(char ch,attr_t attr){
      if(ch=='\n'){
	MoveCursor(0,cury+1);
      }
      else if(IsDrawable()){
	if(IsTransparent){
	  auto a=inch();
	  if(ch==L' '){
	    ch=a&(A_CHARTEXT);
	  }
	  if(attr&A_COLOR)
	    a=a&(~A_COLOR);
	  a=a&A_ATTRIBUTES;
	  attr=attr|a;
	}
	attron(attr);
	addch(ch);
	attroff(attr);
	MoveCursor(curx+mk_wcwidth(ch),cury);
      }
    }
    
    void AddStr(std::wstring str,attr_t attr){
      for(auto ch:str){
	AddChar(ch,attr);
      }
    }
    
    void AddStr(std::string str,attr_t attr){
      for(auto ch:str){
	AddChar(ch,attr);
      }
    }
    
    void MoveCursor(int px,int py){
      curx=px;
      cury=py;
      if(IsCursorOnScreen()){
	move(y+cury,x+curx);
      }
    }

    bool IsDrawable(){
      return IsCursorOnScreen() && curx<width && cury<height && curx>=0 && cury>=0;
    }
    
    bool IsCursorOnScreen(){
      int screenw,screenh;
      getmaxyx(stdscr,screenh,screenw);
      if(x+curx<screenw && y+cury<screenh && x+curx>=0 && y+cury>=0)
	return true;
      return false;
    }

    std::vector<int> GetCursor(){
      std::vector<int> vect{curx,cury};
      return vect;
    }
    
    std::vector<int> GetSize(){
      std::vector<int> vect{width,height};
      return vect;      
    }
  };
}
