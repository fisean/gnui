#pragma once
#include <xcb/xcb.h>
#include <gnui/display.h>


namespace gnui
{
class XCBDisplay : public Display
{
  public:
    XCBDisplay();
    ~XCBDisplay();

    virtual void line(
      const int &x0,
      const int &y0,
      const int &x1,
      const int &y1
    );
    virtual int run();

  protected:
    xcb_connection_t *_connection;
    xcb_screen_t *_screen;
    xcb_drawable_t _window;
    xcb_gcontext_t _foreground;
    uint32_t _values[2];
    uint32_t _mask;
}; // Display
} // namespace
