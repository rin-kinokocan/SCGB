#pragma once
#include <curses.h>
#include "define.hpp"
#include "Boundary.hpp"


namespace scgb{
  class DrawingComponent{
  public:
    virtual void Draw()=0;
    void SetOrigin(int x,int y){
      origin[0]=x;
      origin[1]=y;
    }
    void SetBoundary(Boundary &b){
      boundary=&b;
    }

  private:
    // cursor positions
    int x=0;
    int y=0;
    // pointer to the boundary rectangle.
    Vector2D origin;
    Boundary *boundary=nullptr;
    
  protected:
    Vector2D GetCursor(){
      // Get absolute coordinate of cursor.
      return Vector2D(origin[0]+x,origin[1]+y);
    }
    
    void InitDraw(){
      MoveCursor(0,0);
    }

    void ChangeLine(){
      MoveCursor(0,y+1);      
    }
    
    void AddChar(wchar_t ch,attr_t attr){
      if(ch==L'\n'){
	ChangeLine();
	return;
      }
      if(IsDrawable()){
	std::wstring str(1,ch);
	cchar_t c;
	setcchar(&c,str.c_str(),attr,0,nullptr);
	attron(attr);
	add_wchnstr(&c,1);
	attroff(attr);
      }
      MoveCursor(x+mk_wcwidth(ch),y);
    }
    
    void AddChar(wchar_t ch,attr_t attr,int x,int y){
      MoveCursor(x,y);
      AddChar(ch,attr);
    }
    
    void AddStr(std::wstring str,attr_t attr){
      for(auto ch:str){
	AddChar(ch,attr);
      }
    }
    
    void AddStr(std::wstring str,attr_t attr,int x,int y){
      MoveCursor(x,y);
      AddStr(str,attr);
    }
       
    void MoveCursor(int px,int py){
      this->x=px;
      this->y=py;
      if(IsCursorOnScreen()){
	auto p=GetCursor();
	move(p[1],p[0]);
      }
    }
   
    bool IsCursorOnScreen(){
      auto m=Util::GetMaxScr();
      auto c=GetCursor();
      if(c[0]<0 || c[1]<0)
	return false;
      if(c[0]<m[0] && c[1]<m[1])
	return true;
      return false;
    }

    bool IsDrawable(){
      if(!boundary)
	return IsCursorOnScreen();
      auto ul=boundary->GetUpLeft();
      auto br=boundary->GetBottomRight();
      auto c=GetCursor();
      if(c[0]>=ul[0] && c[0]<=br[0] && c[1]>=ul[1] && c[1]<=br[1]){
	return IsCursorOnScreen();
      }
      else
	return false;
    }
  };
}
