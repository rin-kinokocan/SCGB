#include "BaseModel.hpp"

namespace scgb{
  class String:public BaseModel<std::wstring>{
  public:
    std::wstring string;
    std::wstring GetData(){return string;}
    void SetData(std::wstring str){
      string=str;
    }
    explicit String(std::wstring str){string=str;}
  };
}
