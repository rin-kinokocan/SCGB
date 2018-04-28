#pragma once
#include <ncurses.h>
#include <memory>
#include "Movable.hh"
#include "../include/define.h"

namespace scgb{
  class GameWindow :public BaseWindow{//Used as base class of all windows.
  private:
    virtual void Init(int width,int height) =0;
  protected:
    scgb::DrawList drawentity;
    
  public:    
    virtual void Refresh()=0;
    virtual void Destroy()=0;
    virtual void GetProperty(int ary[])=0;
     
    virtual bool AddDrawable(Layer l,pDrawable pd){
      if(this->drawentity.find(l)==this->drawentity.end())
	this->drawentity.insert(std::pair<Layer,pDrawable>(l,pd));
      else
	return false;
      return true;	 
    };
    virtual void RemoveDrawable(DrawList::iterator i){this->drawentity.erase(i);};
    virtual pDrawable& GetDrawable(Layer l){return this->drawentity.find(l)->second;};
    
    virtual ~GameWindow(){};
  };

}
