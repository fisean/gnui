#include <gnui/window.h>


using namespace gnui;


Window::Window(
  const int &x,
  const int &y,
  const int &w,
  const int &h
)
  : Widget(x, y, w, h)
{
  _handler = display->create(x, y, w, h);
}
