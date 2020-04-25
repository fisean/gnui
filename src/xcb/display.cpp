#include <iostream>
#include <gnui/basegroup.h>
#include <gnui/xcb/display.h>


using namespace gnui;


XCBDisplay::XCBDisplay()
{
  _connection = xcb_connect(nullptr, nullptr);
  _screen = xcb_setup_roots_iterator(xcb_get_setup(_connection)).data;
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
  // xcb_poly_line(
    // _connection,
    // XCB_COORD_MODE_PREVIOUS,
    // _window,
    // _foreground,
    // 2,
    // lines
  // );
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
      case XCB_EXPOSE:
      {
        break;
      }
      default:
        /* Unknown event type, ignore it */
        break;
    }
    free (event);
  }
  return 0;
}


Handler *
XCBDisplay::create(
  const int &x,
  const int &y,
  const int &w,
  const int &h,
  const Widget * const widget
)
{
  xcb_gcontext_t foreground;
  Handler *handler = new Handler();
  auto &parent = BaseGroup::current == nullptr || widget->type() == "window"
    ? _screen->root
    : BaseGroup::current->handler()->xcb_window;
  handler->xcb_window = xcb_generate_id(_connection);
  uint32_t mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
  uint32_t values[] =
  {
    _screen->white_pixel,
    XCB_EVENT_MASK_EXPOSURE       | XCB_EVENT_MASK_BUTTON_PRESS   |
    XCB_EVENT_MASK_BUTTON_RELEASE | XCB_EVENT_MASK_POINTER_MOTION |
    XCB_EVENT_MASK_ENTER_WINDOW   | XCB_EVENT_MASK_LEAVE_WINDOW   |
    XCB_EVENT_MASK_KEY_PRESS      | XCB_EVENT_MASK_KEY_RELEASE
  };

  xcb_create_window(
    _connection,                   /* connection          */
    XCB_COPY_FROM_PARENT,          /* depth               */
    handler->xcb_window,           /* window Id           */
    parent,                        /* parent window       */
    x, y,                          /* x, y                */
    w, h,                          /* width, height       */
    10,                             /* border_width        */
    XCB_WINDOW_CLASS_INPUT_OUTPUT, /* class               */
    _screen->root_visual,          /* visual              */
    mask, values                   /* masks */
  );

  /* Map the window on the screen and flush*/
  xcb_map_window(_connection, handler->xcb_window);
  xcb_flush(_connection);
  return handler;
}
