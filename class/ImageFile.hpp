#pragma once
#include <vector>

namespace scgb{
  class ImageFile{
  public:
    std::vector<int> GetSize(){
      std::vector<int> vec{width,height};
      return vec;
    }
    const std::vector<attr_t>& GetData(){
      return pixels;
    }
  protected:
    std::vector<attr_t> pixels;
    int width=0;
    int height=0;
    virtual void LoadImage(std::string filename)=0;
  };
}
