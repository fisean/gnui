#include <iostream>
#include <gnui/button.h>
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
    auto button = new Button(50, 50, 50, 50, "Button");
  }
  win->end();
  return Engine::run();
}
