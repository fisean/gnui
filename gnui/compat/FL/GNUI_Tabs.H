#ifndef GNUI_Tabs_H
#define GNUI_Tabs_H

#include "GNUI_Group.H"
#include <gnui/TabGroup.h>

class GNUI_Tabs : public gnui::TabGroup {

public:
  GNUI_Tabs(int x, int y, int w, int h, const char*l = 0)
    : gnui::TabGroup(x,y,w,h,l) {begin();}
};

#endif

