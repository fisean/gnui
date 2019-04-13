#ifndef Fl_Pack_H
#define Fl_Pack_H

#include "Fl_Group.H"
#include <gnui/PackedGroup.h>

class Fl_Pack : public gnui::PackedGroup {

public:
  Fl_Pack(int x, int y, int w, int h, const char*l = 0)
    : gnui::PackedGroup(x,y,w,h,l) {begin();}

}; // Fl_Pack class

#endif
