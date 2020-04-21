#include <gnui/engine.h>
#include <gnui/widget.h>
#include <gnui/xcb/display.h>


using namespace gnui;


void
Engine::init()
{
  Widget::display = new XCBDisplay();
}


int
Engine::run(const std::string &displayName)
{
  auto result = Widget::display->run();
  delete Widget::display;
  Widget::display = nullptr;
  return result;
}
