#pragma once
#include <gnui/widget.h>


namespace gnui
{
class Button : public Widget
{
  public:
    Button(
      const int &x,
      const int &y,
      const int &w,
      const int &h,
      const std::string &label
    );
  protected:
}; // Button
} // namespace
