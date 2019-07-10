#ifndef GNUI_Scroll_H
#define GNUI_Scroll_H

#include "GNUI_Group.H"
#include <gnui/ScrollGroup.h>

class GNUI_Scroll : public gnui::ScrollGroup {

public:
  GNUI_Scroll(int x, int y, int w, int h, const char*l = 0)
    : gnui::ScrollGroup(x,y,w,h,l) {begin();}
};

#endif

