#pragma once
#include <gnui/display.h>

namespace xorg
{
#include <X11/Xlib.h>
}


namespace gnui
{
class Widget;
class XorgDisplay : public Display
{
  public:
    XorgDisplay();
    ~XorgDisplay();

    virtual int run();
    virtual void line(
      const int &x0,
      const int &y0,
      const int &x1,
      const int &y1
    );
    virtual Handler * create(
      const int &x,
      const int &y,
      const int &w,
      const int &h,
      const Widget * const widget
    );
    virtual void drawLabel(Widget *widget, int x1, int y1);

  protected:
    int _scr;
    xorg::Display *_dpy;
    xorg::Visual *_visual;
}; // XorgDisplay
} // namespace
