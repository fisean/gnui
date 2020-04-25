#include <iostream>
#include <gnui/engine.h>
#include <gnui/window.h>


using namespace gnui;


int
main()
{
  Engine::init();
  Window *win = new Window(0, 0, 150, 150);
  win->begin();
  {
    Window *win2 = new Window(50, 50, 50, 50);
  }
  win->end();
  return Engine::run();
}
