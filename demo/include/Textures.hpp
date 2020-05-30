#pragma once
#include "AAfile.hpp"
#include <map>
#include <string>

namespace Invader{
  class Textures{
  private:
    std::map<std::string,scgb::AAfile> texturemap;
  public:
    scgb::AAfile& operator[](std::string name){
      try{
	return texturemap.at(name);
      }
      catch(std::out_of_range e){
	// Maybe?
      }
    }
    void Set(std::string name,std::string path){
      texturemap[name]=scgb::AAfile(path);
    }
    void Erase(std::string name){
      texturemap.erase(name);
    }
  };
}
