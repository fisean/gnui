#pragma once
#include <string>
#include <gnui/display.h>
#include <gnui/handler.h>


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
      const int &h,
      const std::string &label = ""
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
    Handler * handler();
    void label(const std::string &l);
    std::string label();
    const std::string type() const;

    friend class Engine;

  protected:
    int _x;
    int _y;
    int _width;
    int _height;
    Widget *_next;
    Widget *_previous;
    Handler *_handler;
    std::string _label;
    std::string _type;

    static Display *display;
    static Widget *_widgets;
}; // Widget
} // namespace
