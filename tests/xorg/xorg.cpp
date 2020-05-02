#include <iostream>
#include <string>
#include <X11/Xft/Xft.h>


static void
die(const std::string &msg)
{
  std::cerr << msg << '\n';
  exit(1);
}


int
main()
{
    auto dpy = XOpenDisplay(NULL);
    if (!dpy)
    {
      die("cannot open X11 display");
    }
    int scr = DefaultScreen(dpy);
    auto visual = DefaultVisual(dpy, scr);
    Colormap cmap = DefaultColormap(dpy, scr);
    Window win = XCreateSimpleWindow(dpy, RootWindow(dpy, scr), 100, 100, 200, 100, 1, BlackPixel(dpy, scr), WhitePixel(dpy, scr));
    XSelectInput(dpy, win, ExposureMask | KeyPressMask);
    XMapWindow(dpy, win);
    std::string fontname{"DejaVu Sans Mono:size=11:antialias=true"};
    auto font = XftFontOpenName(dpy, scr, fontname.data());
    if (!font)
    {
      die("cannot load font");
    }
    XftColor color;
    if (!XftColorAllocName(dpy, visual, cmap, "#0000ee", &color))
    {
      die("cannot allocate xft color");
    }
    XftDraw *draw = XftDrawCreate(dpy, win, visual, cmap);

    while(1)
    {
      XEvent ev;

      XNextEvent(dpy, &ev);
      if (ev.type == Expose)
      {
        XftDrawStringUtf8(draw, &color, font, 50, 50, (const FcChar8 *)"Hello Xft!", 10);
      }
      else if (ev.type == KeyPress)
      {
        break;
      }
    }

    /* Cleanup. Not necessary, only for the sake of completeness. */
    XftColorFree(dpy, visual, cmap, &color);
    XftDrawDestroy(draw);
    XDestroyWindow(dpy, win);
    XCloseDisplay(dpy);
}
