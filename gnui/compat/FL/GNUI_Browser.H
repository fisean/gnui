#ifndef GNUI_Browser_H
#define GNUI_Browser_H

#include "GNUI_Scrollbar.H"
#include "GNUI_Menu_.H"
#include <gnui/Browser.h>
class GNUI_Browser : public gnui::Browser {
public:
  GNUI_Browser(int x, int y, int w, int h, const char* l = 0)
    :gnui::Browser(x,y,w,h,l) {}

  void make_visible(int n) {goto_index(n); make_item_visible();}
  bool load(const char* fname) {/* NYI */ return true;}
  void position(int y) {goto_position(y);}
};

enum {
  GNUI_NORMAL_BROWSER	= gnui::Browser::NORMAL,
  GNUI_SELECT_BROWSER	= gnui::Browser::NORMAL,
  GNUI_HOLD_BROWSER	= gnui::Browser::NORMAL,
  GNUI_MULTI_BROWSER	= gnui::Browser::MULTI
};

#endif
