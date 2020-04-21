#include <iostream>
#include <gnui/xcb/display.h>


using namespace gnui;


XCBDisplay::XCBDisplay()
{
  _connection = xcb_connect(nullptr, nullptr);
  _screen = xcb_setup_roots_iterator(xcb_get_setup(_connection)).data;
  _window = _screen->root;
  _foreground = xcb_generate_id(_connection);
  _mask = XCB_GC_FOREGROUND | XCB_GC_GRAPHICS_EXPOSURES;
  _values[0] = 234351;
  _values[1] = 0;
  xcb_create_gc(_connection, _foreground, _window, _mask, _values);
  _window = xcb_generate_id(_connection);
  _mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
  _values[0] = _screen->black_pixel;
  _values[1] = XCB_EVENT_MASK_EXPOSURE;

  xcb_create_window(
    _connection,                   /* connection          */
    XCB_COPY_FROM_PARENT,          /* depth               */
    _window,                       /* window Id           */
    _screen->root,                 /* parent window       */
    0, 0,                          /* x, y                */
    150, 150,                      /* width, height       */
    10,                            /* border_width        */
    XCB_WINDOW_CLASS_INPUT_OUTPUT, /* class               */
    _screen->root_visual,          /* visual              */
    _mask, _values                 /* masks */
  );

  /* Map the window on the screen and flush*/
  xcb_map_window(_connection, _window);
  xcb_flush(_connection);
  xcb_generic_event_t *event;
  while ((event = xcb_wait_for_event(_connection)))
  {
    if ((event->response_type & ~0x80) == XCB_EXPOSE) { return; }
  }
}


XCBDisplay::~XCBDisplay() { xcb_disconnect(_connection); }


void
XCBDisplay::line(
  const int &x0,
  const int &y0,
  const int &x1,
  const int &y1
)
{
  xcb_point_t lines[] =
  {
    {(short)x0, (short)y0},
    {(short)x1, (short)y1}
  };
  xcb_poly_line(
    _connection,
    XCB_COORD_MODE_PREVIOUS,
    _window,
    _foreground,
    2,
    lines
  );
  xcb_flush(_connection);
}


int
XCBDisplay::run()
{
  xcb_flush(_connection);
  xcb_generic_event_t *event;
  while ((event = xcb_wait_for_event(_connection)))
  {
    auto rtype = event->response_type & ~0x80;
    switch (rtype)
    {
      default:
        /* Unknown event type, ignore it */
        break;
    }
    free (event);
  }
  return 0;
}
