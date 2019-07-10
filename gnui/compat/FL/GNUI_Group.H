#ifndef GNUI_Group_H
#define GNUI_Group_H

#include "GNUI_Widget.H"
#include <gnui/Group.h>

class GNUI_Group : public gnui::Group {

public:
  GNUI_Group(int x, int y, int w, int h, const char*l = 0)
    : gnui::Group(x,y,w,h,l) {begin();}
  static GNUI_Group* current() {return (GNUI_Group*)(gnui::Group::current());}
};

#endif

