#pragma once
#include <gnui/display.h>
#include <gnui/widget.h>


namespace gnui
{
class BaseGroup : public Widget
{
  public:
    BaseGroup(
      const int &x,
      const int &y,
      const int &w,
      const int &h,
      const std::string &label = ""
    );

    static BaseGroup *current;

    Widget * children();
    void add(Widget *child);
    void remove(Widget *child);
    void begin();
    void end();

  protected:
    BaseGroup *_previousGroup;
    Widget *_children;
    Widget *_last;
}; // Widget
} // namespace
