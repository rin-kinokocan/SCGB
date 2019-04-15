#pragma once
#include <string>
#include <sstream>
#include <fstream>

namespace scgb{
  class AAfile{
  public:
    const std::wstring& GetString(){
      return data;
    }
    void SetFile(std::string filename){
      std::wifstream wif(filename,std::ios::binary);
      std::wstringstream wss;
      if(!wif.is_open())
	return;
      wss<<wif.rdbuf();
      data=wss.str();
    }
  protected:
    std::wstring data;
  };
}
