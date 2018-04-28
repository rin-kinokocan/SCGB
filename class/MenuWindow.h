#include <ncurses.h>
#include "GameWindow.h"

namespace scgb{
  class MenuWindow :public GameWindow{
  private:
      void Init(int width,int height);
  public:
      WINDOW* testwin;
      MenuWindow(int width,int height);
      void Draw();
      void Clear();
      void Destroy();
      void GetProperty(int[]);
      scgb::Event GetEvent();
      
      WINDOW* test();
      ~MenuWindow();      
  };
}
