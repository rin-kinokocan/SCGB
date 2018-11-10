#pragma once

namespace scgb{
  class Screen{
    //ncurses initialize+refresh.
  public:
    void Refresh();
    void OnResize();
    void Init();
  };
}
