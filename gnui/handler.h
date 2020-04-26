#pragma once
#include <gnui/config.h>
#ifdef DISPLAY_XCB
#include <xcb/xcb.h>
#endif


class Handler
{
  public:
#ifdef DISPLAY_XCB
    xcb_drawable_t xcb_window;
    xcb_gcontext_t gc;
    xcb_font_t font;
#endif
};
