#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

namespace scgb{
  class AAfile{
  private:
    int width;
    int height;
    std::wstring data;
  public:
    std::vector<int> GetSize(){
      std::vector<int> vect{width,height};
      return vect;
    } 
    const std::wstring& GetData(){
      return data;
    }
    void LoadFile(std::string filename){
      std::wifstream wif(filename,std::ios::binary);
      std::wstringstream wss;
      if(!wif.is_open()){
	endwin();
	throw(std::runtime_error("FILE_NOT_FOUND"));
      }
      wss<<wif.rdbuf();
      data=wss.str();
      int count=0;
      width=0;height=0;
      for(auto s:data){
	if(s=='\n'){
	  if(count>width)
	    width=count;
	  count=0;
	  height+=1;
	}
	else
	  count+=1;
      }
      width++;
    }
    
    AAfile(std::string filename){
      LoadFile(filename);
    }
    
  };
}
