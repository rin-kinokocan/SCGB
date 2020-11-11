#pragma once
#include <chrono>
#include <thread>

namespace scgb{
  class Clock{
  private:
    int fps;
    int dt;
  public:
    int GetDeltaTime(){
      return dt;
    }
    void WaitFrame(){
      // wait a frame
      auto a=std::chrono::high_resolution_clock::now();
      auto b=std::chrono::high_resolution_clock::now();
      int t;
      do{
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	b=std::chrono::high_resolution_clock::now();
	t=std::chrono::duration_cast<std::chrono::milliseconds>(b-a).count();
      }while(t<1000/fps);
      dt=std::chrono::duration_cast<std::chrono::milliseconds>(b-a).count();
    }
    void SetFPS(int i){
      fps=i;
    }
    Clock(int fps=10){
      this->fps=fps;
    }
  };
}
