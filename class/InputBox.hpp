#pragma once
#include "DrawingComponent.hpp"

namespace scgb{
  class InputBox:public DrawingComponent{
    // flickers every 4 clocks.
  protected:
    std::wstring str=L"";
    int position=0;
    int count=0;
    bool state=false;
    int GetPos(){
      int pos=0,c=0;
      for(int i=0;i<position;i++){
	pos+=mk_wcwidth(str[i]);
      }
      return pos;
    }
  public:
    InputBox(int x=0,int y=0,int w=10):DrawingComponent(x,y,w,1){
      IsTransparent=true;
    }
    void Draw(){
      MoveCursor(0,0);
      AddStr(str,0);
      if(state==true){
      	MoveCursor(GetPos(),0);
      	AddChar(L'█',0);
      }
      if(count<4){
      	count++;
      }
      else{
      	count=0;
	state=!state;
      }
    }
    void MovePosition(int pos){
      if(pos<=str.length() && pos>=0){
	position=pos;
      }
    }
    void HandleInput(int code,wint_t input){
      switch(input){
      case KEY_LEFT:
	MovePosition(position-1);
	break;
      case KEY_RIGHT:
	MovePosition(position+1);
	break;
      case KEY_ENTER:
      case L'\n':
	break;
      case KEY_BACKSPACE:
	DeleteChar();
      default:
	if(code!=ERR && code!=KEY_CODE_YES){
	  InsertChar(input);
	}
	break;
      }
    }
    void InsertChar(wchar_t ch){
      if(GetPos()+mk_wcwidth(ch)<width){
	str.insert(str.begin()+position,ch);
	position+=1;
      }
    }
    
    void DeleteChar(){
      if(position!=0){
	str.erase(str.begin()+position-1);
	position-=1;
      }
      
    }
  };
}
