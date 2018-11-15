#include <chrono>
#include "../include/define.h"

using namespace scgb

typedef int clocktime;
typedef int milliclocktime;
typedef int microclocktime;

class Clock{
private:
  std::chrono::steady_clock;
  microclocktime time;
  microclocktime pretime;
public:
  clocktime GetTimeSecond();
  milliclocktime GetTimeMilliSecond();
  microclocktime GetTimeMicroSecond();
  microclocktime GetErapsedTime();

  Clock();
}
