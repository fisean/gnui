#pragma once
#include <gnui/basegroup.h>


namespace gnui
{
class Group : public BaseGroup
{
  public:
    Group(
      const int &x,
      const int &y,
      const int &w,
      const int &h,
      const std::string &label = ""
    );
  protected:
}; // Group
} // namespace
