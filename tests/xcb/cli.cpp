#include <iostream>
#include <gnui/button.h>
#include <gnui/engine.h>
#include <gnui/window.h>


using namespace gnui;


int
main()
{
  Engine::init();
  Window *win = new Window(0, 0, 500, 500);
  win->begin();
  {
    auto button = new Button(10, 10, 400, 400, "Button");
  }
  win->end();
  return Engine::run();
}
