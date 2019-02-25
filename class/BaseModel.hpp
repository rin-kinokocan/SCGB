#pragma once
namespace scgb{
  template <class T>
  class BaseModel{
    // Contains data.
  public:
    virtual T GetData()=0;
  };
}
