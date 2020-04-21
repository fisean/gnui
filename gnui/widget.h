#pragma once
#include <gnui/display.h>


namespace gnui
{
class Engine;
class Widget
{
  public:
    Widget(
      const int &x,
      const int &y,
      const int &w,
      const int &h
    );


    int x();
    int y();
    int width();
    int height();
    void x(const int &_x);
    void y(const int &_y);
    void width(const int &_w);
    void height(const int &_h);
    Widget * next();
    Widget * previous();
    void next(Widget *n);
    void previous(Widget *p);

    friend class Engine;

  protected:
    int _x;
    int _y;
    int _width;
    int _height;
    Widget *_next;
    Widget *_previous;
    static Display * display;
}; // Widget
} // namespace
