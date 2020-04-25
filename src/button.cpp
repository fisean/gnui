#include <gnui/button.h>


using namespace gnui;


Button::Button(
  const int &x,
  const int &y,
  const int &w,
  const int &h,
  const std::string &label
)
  : Widget(x, y, w, h, label)
{
  _type = "button";
  _handler = display->create(x, y, w, h, this);
}
