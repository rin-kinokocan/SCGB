#pragma once
namespace scgb{
  template <class T>
  class BaseModel{
    // Contains data, and can update them.
  public:
    virtual T GetData()=0;
  };
}
