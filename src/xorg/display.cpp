#include <gnui/basegroup.h>
#include <gnui/xorg/display.h>

namespace xorg
{
#include <X11/Xft/Xft.h>
}


using namespace gnui;
using namespace xorg;


XorgDisplay::XorgDisplay()
{
  _dpy = xorg::XOpenDisplay(nullptr);
  _scr = DefaultScreen(_dpy);
  _visual = DefaultVisual(_dpy, _scr);
}


XorgDisplay::~XorgDisplay()
{
}


int
XorgDisplay::run()
{
  while(1)
  {
    xorg::XEvent ev;

    xorg::XNextEvent(_dpy, &ev);
    if (ev.type == Expose)
    {
      for (auto widget = Widget::begining(); widget != nullptr; widget = widget->next())
      {
        widget->draw();
      }
    }
    else if (ev.type == KeyPress)
    {
      break;
    }
  }
  return 0;
}


void
XorgDisplay::line(
  const int &x0,
  const int &y0,
  const int &x1,
  const int &y1
)
{}


Handler *
XorgDisplay::create(
  const int &x,
  const int &y,
  const int &w,
  const int &h,
  const Widget * const widget
)
{
  Handler *handler = new Handler();
  auto parent = widget->type() == "window"
    ? RootWindow(_dpy, _scr)
    : BaseGroup::current->handler()->win;

  handler->win = XCreateSimpleWindow(
    _dpy,
    parent,
    x, y,
    w, h,
    1,
    BlackPixel(_dpy, _scr),
    WhitePixel(_dpy, _scr)
  );
  XSelectInput(_dpy, handler->win, ExposureMask | KeyPressMask);
  XMapWindow(_dpy, handler->win);
  return handler;
}


void
XorgDisplay::drawLabel(Widget *widget, int x, int y)
{
  Colormap cmap = DefaultColormap(_dpy, _scr);
  XftColor color;
  XftColorAllocName(_dpy, _visual, cmap, "#0000ee", &color);
  std::string fontname{"DejaVu Sans Mono:size=11:antialias=true"};
  auto font = XftFontOpenName(_dpy, _scr, fontname.data());
  XftDraw *draw = XftDrawCreate(_dpy, widget->handler()->win, _visual, cmap);
  XftDrawStringUtf8(draw, &color, font, x, y, (const FcChar8 *)widget->label().data(), widget->label().size());
}
