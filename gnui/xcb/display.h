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
    virtual Handler * create(
      const int &x,
      const int &y,
      const int &w,
      const int &h
    );

  protected:
    xcb_connection_t *_connection;
    xcb_screen_t *_screen;
}; // Display
} // namespace
