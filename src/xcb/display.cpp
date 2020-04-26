#include <iostream>
#include <xcb/xproto.h>
#include <gnui/basegroup.h>
#include <gnui/xcb/display.h>


using namespace gnui;


static uint32_t
widget2value(const Widget * const widget)
{
  if (widget->type() == "window")
  {
    return
      XCB_EVENT_MASK_EXPOSURE       | XCB_EVENT_MASK_BUTTON_PRESS   |
      XCB_EVENT_MASK_BUTTON_RELEASE | XCB_EVENT_MASK_POINTER_MOTION |
      XCB_EVENT_MASK_ENTER_WINDOW   | XCB_EVENT_MASK_LEAVE_WINDOW   |
      XCB_EVENT_MASK_KEY_PRESS      | XCB_EVENT_MASK_KEY_RELEASE    ;
  }
  if (widget->type() == "button")
  {
    return
      XCB_EVENT_MASK_EXPOSURE       | XCB_EVENT_MASK_BUTTON_PRESS   |
      XCB_EVENT_MASK_BUTTON_RELEASE | XCB_EVENT_MASK_ENTER_WINDOW   |
      XCB_EVENT_MASK_KEY_PRESS      | XCB_EVENT_MASK_KEY_RELEASE    ;
  }
  return 0;
}


static xcb_gcontext_t
getFontGC(
  xcb_connection_t *connection,
  xcb_screen_t *screen,
  xcb_window_t window,
  const std::string &font_name
)
{
    /* get font */
    xcb_font_t font = xcb_generate_id(connection);
    xcb_void_cookie_t fontCookie = xcb_open_font_checked
    (
      connection,
      font,
      font_name.size(),
      font_name.data()
    );

    /* create graphics context */
    xcb_gcontext_t gc = xcb_generate_id(connection);
    uint32_t mask = XCB_GC_FOREGROUND | XCB_GC_BACKGROUND | XCB_GC_FONT;
    uint32_t value_list[] =
    {
      screen->black_pixel,
      screen->white_pixel,
      font
    };
    xcb_void_cookie_t gcCookie = xcb_create_gc_checked
    (
      connection,
      gc,
      window,
      mask,
      value_list
    );

    /* close font */
    fontCookie = xcb_close_font_checked(connection, font);
    return gc;
}


static void
drawText(
  xcb_connection_t *connection,
  xcb_screen_t *screen,
  xcb_window_t window,
  int16_t x1,
  int16_t y1,
  const std::string &label = ""
)
{
  /* get graphics context */
  xcb_gcontext_t gc = getFontGC(connection, screen, window, "fixed");

  /* draw the text */
  xcb_void_cookie_t textCookie = xcb_image_text_8_checked
  (
    connection,
    label.size(),
    window,
    gc,
    x1, y1,
    label.data()
  );

  /* free the gc */
  xcb_void_cookie_t gcCookie = xcb_free_gc(connection, gc);
}


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
    widget2value(widget)
  };

  xcb_create_window(
    _connection,                   /* connection          */
    XCB_COPY_FROM_PARENT,          /* depth               */
    handler->xcb_window,           /* window Id           */
    parent,                        /* parent window       */
    x, y,                          /* x, y                */
    w, h,                          /* width, height       */
    1,                             /* border_width        */
    XCB_WINDOW_CLASS_INPUT_OUTPUT, /* class               */
    _screen->root_visual,          /* visual              */
    mask, values                   /* masks */
  );

  /* Map the window on the screen and flush*/
  xcb_map_window(_connection, handler->xcb_window);
  xcb_flush(_connection);
  return handler;
}
