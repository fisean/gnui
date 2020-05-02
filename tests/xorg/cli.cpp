#include <gnui/button.h>
#include <gnui/group.h>
#include <gnui/engine.h>
#include <gnui/window.h>


using namespace gnui;


int
main()
{
  Engine::init();
  auto win = new Window(0, 0, 500, 500);
  win->begin();
  {
    auto group = new Group(100, 100, 100, 100);
    group->begin();
    {
      auto button = new Button(10, 10, 50, 50, "Nešto");
    }
    group->end();
  }
  win->end();
  return Engine::run();
}
