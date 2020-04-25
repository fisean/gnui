#pragma once
#include <gnui/handler.h>


namespace gnui
{
class Widget;
class Display
{
  public:
    Display();
    virtual ~Display();

    virtual int run();
    virtual void line(
      const int &x0,
      const int &y0,
      const int &x1,
      const int &y1
    ) = 0;
    virtual Handler * create(
      const int &x,
      const int &y,
      const int &w,
      const int &h,
      const Widget * const widget
    ) = 0;

  protected:
}; // Display
} // namespace
