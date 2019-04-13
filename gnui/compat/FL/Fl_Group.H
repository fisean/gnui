#ifndef Fl_Group_H
#define Fl_Group_H

#include "Fl_Widget.H"
#include <gnui/Group.h>

class Fl_Group : public gnui::Group {

public:
  Fl_Group(int x, int y, int w, int h, const char*l = 0)
    : gnui::Group(x,y,w,h,l) {begin();}
  static Fl_Group* current() {return (Fl_Group*)(gnui::Group::current());}
};

#endif

