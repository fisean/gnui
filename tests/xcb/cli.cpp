#include <unistd.h>      /* pause() */
#include <thread>
#include <chrono>
#include <gnui/xcb/display.h>
#include <gnui/engine.h>


using namespace gnui;


int
main()
{
  Engine::init();
  // Engine::active->line(0, 0, 50, 200);
  return Engine::run();
}
