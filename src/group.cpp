#include <gnui/group.h>


using namespace gnui;


Group::Group(
  const int &x,
  const int &y,
  const int &w,
  const int &h,
  const std::string &label
)
  : BaseGroup(x, y, w, h, label)
{
  _type = "group";
  _handler = display->create(x, y, w, h, this);
}
