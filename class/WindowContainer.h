#pragma once
#include "Drawable.h"

namespace scgb{
  class WindowContainer:public Drawable{
  protected:
    std::map<int,scgb::pDrawable> drawentity;
    SizeData sd;
    bool isHidden=false;
  public:
    virtual void Draw();
    virtual void Refresh();
    virtual void OnResize();
    virtual void Hide();
    virtual void Show();
    
    template <class T>
    WeakPtr<T> AddDrawable(int l,DrawableBuilder* db){
      if(drawentity.find(l)==drawentity.end()){
	std::shared_ptr<Drawable> b;
	db->SetPSD(&sd);
	b.reset(db->GetResult());
	drawentity.insert(std::pair<int,pDrawable>(l,b));
	return WeakPtr<T>(std::static_pointer_cast<T>(b));
      }
      else{
	std::string info="the layer ";
	info+=std::to_string(l);info+="is already used";
	endwin();
	throw std::runtime_error(info);
      }
    };
    virtual void DeleteDrawable(int l);
    
    WindowContainer(double,double,int,int,SizeData*,SizeData);
    WindowContainer(double,double,int,int,SizeData*);
    virtual ~WindowContainer(){
      drawentity.clear();
    };
  };
  
  class WCBuilder:public DrawableBuilder{
  public:
    virtual Drawable* GetResult(){
      SizeData sd;
      return new WindowContainer(x,y,w,h,psd,sd);
    };
    WCBuilder(double x,double y,int w,int h)
      :DrawableBuilder(x,y,w,h){};
    virtual ~WCBuilder(){};
  };
}
