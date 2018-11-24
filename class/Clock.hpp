#pragma once
#include <chrono>
#include <thread>

namespace scgb{
  class Clock{
  private:
    static int FPS;
    static int dt;
  public:
    static int GetDeltaTime(){
      return dt;
    }
    void WaitFrame(){
      // inclements clock one frame.
      // You SHOULD NOT call WaitFrame in
      // anywhere other than your main game loop.
      auto a=std::chrono::high_resolution_clock::now();
      auto b=std::chrono::high_resolution_clock::now();
      int t;
      do{
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	b=std::chrono::high_resolution_clock::now();
	t=std::chrono::duration_cast<std::chrono::milliseconds>(b-a).count();
      }while(t<1000/FPS);
      dt=std::chrono::duration_cast<std::chrono::milliseconds>(b-a).count();
    }
    void SetFPS(int i){
      FPS=i;
    }
  };
  int Clock::FPS=30;
  int Clock::dt=0;
}


