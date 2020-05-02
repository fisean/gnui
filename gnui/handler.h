#pragma once
#include <gnui/config.h>
#ifdef DISPLAY_XORG
namespace xorg
{
#include <X11/X.h>
}
#endif


class Handler
{
  public:
#ifdef DISPLAY_XORG
    xorg::Window win;
#endif
};
