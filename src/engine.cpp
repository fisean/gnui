#include <gnui/engine.h>
#include <gnui/widget.h>
#include <gnui/xorg/display.h>


using namespace gnui;


void
Engine::init()
{
  Widget::display = new XorgDisplay();
}


int
Engine::run()
{
  auto result = Widget::display->run();
  delete Widget::display;
  Widget::display = nullptr;
  return result;
}
