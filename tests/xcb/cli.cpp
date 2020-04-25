#include <gnui/engine.h>
#include <gnui/window.h>


using namespace gnui;


int
main()
{
  Engine::init();
  Window *win = new Window(0, 0, 150, 150);
  return Engine::run();
}
