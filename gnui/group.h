#pragma once
#include <gnui/widget.h>


namespace gnui
{
class Group : public Widget
{
  public:
    Group(
      const int &x,
      const int &y,
      const int &w,
      const int &h
    );

    Widget * children();
    void add(Widget *child);
    void remove(Widget *child);
    void begin();
    void end();

  protected:
    static Group *_current;
    Group *_previous;

    Widget *_children;
    Widget *_last;
}; // Widget
} // namespace
