#ifndef Fl_Scroll_H
#define Fl_Scroll_H

#include "Fl_Group.H"
#include <gnui/ScrollGroup.h>

class Fl_Scroll : public gnui::ScrollGroup {

public:
  Fl_Scroll(int x, int y, int w, int h, const char*l = 0)
    : gnui::ScrollGroup(x,y,w,h,l) {begin();}
};

#endif

