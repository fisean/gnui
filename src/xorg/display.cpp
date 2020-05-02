#include <gnui/basegroup.h>
#include <gnui/xorg/display.h>


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
    if (ev.type == KeyPress)
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
  handler->win = XCreateSimpleWindow(
    _dpy,
    RootWindow(_dpy, _scr),
    100, 100,
    200, 100,
    1,
    BlackPixel(_dpy, _scr),
    WhitePixel(_dpy, _scr)
  );
  XSelectInput(_dpy, handler->win, ExposureMask | KeyPressMask);
  XMapWindow(_dpy, handler->win);
  return handler;
}


void
XorgDisplay::drawLabel(Widget *widget, int x1, int y1)
{}
