#pragma once
class BaseView;
template <class T> class BaseModel;
namespace scgb{
  class BaseController{
  public:
    virtual void Draw()=0;
  };
}
