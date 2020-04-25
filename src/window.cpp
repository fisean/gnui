#include <gnui/window.h>


using namespace gnui;


Window::Window(
  const int &x,
  const int &y,
  const int &w,
  const int &h,
  const std::string &label
)
  : BaseGroup(x, y, w, h, label)
{
  _type = "window";
  _handler = display->create(x, y, w, h, this);
}
