#pragma once
#include "WindowInfo.hpp"

namespace scgb{
  
  class BaseView{
    // Draws something on screen.
  public:
    virtual void Draw()=0;
  private:
    int x=0,y=0;// cursor coordinate
    
    void MoveAfterDraw(wchar_t ch){
      auto w=mk_wcwidth(ch);
      auto g=wi.geometry->GetData();
      if(x+w<g[0]){
	MoveCursor(x+w,y);
      }
      else if(y+1<g[1]){
	MoveCursor(0,y+1);
      }
    }

  protected:
    WindowInfo wi;

    Vector2D GetCursor(){
      // Get absolute coordinate of cursor.
      Vector2D o;
      auto c=wi.coordinate->GetData();
      if(wi.origin)
	o=wi.origin->GetData();
      else
	o=Vector2D(0,0);
      return Vector2D(o[0]+c[0]+x,o[1]+c[1]+y);
    }
    
    void InitDraw(){
      MoveCursor(0,0);
    }
    
    void AddChar(wchar_t ch,attr_t attr){
	if(IsCursorOnScreen()){
	  std::wstring str(1,ch);
	  cchar_t c;
	  setcchar(&c,str.c_str(),attr,0,nullptr);
	  attron(attr);
	  add_wchnstr(&c,1);
	  attroff(attr);
	}
	MoveAfterDraw(ch);
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
      if(IsCursorInBoundary(px,py)){
	x=px;y=py;
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

    bool IsCursorInBoundary(int x,int y){
      Vector2D o;
      auto cursor=GetCursor();
      auto b=wi.boundary->GetData();
      auto c=wi.coordinate->GetData();
      if(wi.origin)
	o=wi.origin->GetData();
      else
	o=Vector2D(0,0);
      if(cursor[0]>=o[0] && cursor[1]>=o[1] && cursor[0]<=o[0]+b[0] && cursor[1]<=o[1]+b[1])
	return true;
      else
	return false;
    }

    explicit BaseView(WindowInfo &windowinfo):wi(windowinfo){}
  };
}
