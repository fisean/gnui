#pragma once
#include <gnui/basegroup.h>


namespace gnui
{
class Window : public BaseGroup
{
  public:
    Window(
      const int &x,
      const int &y,
      const int &w,
      const int &h,
      const std::string &label = ""
    );
    void draw() const;
  protected:
}; // Window
} // namespace
