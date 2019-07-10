#ifndef GNUI_Pack_H
#define GNUI_Pack_H

#include "GNUI_Group.H"
#include <gnui/PackedGroup.h>

class GNUI_Pack : public gnui::PackedGroup {

public:
  GNUI_Pack(int x, int y, int w, int h, const char*l = 0)
    : gnui::PackedGroup(x,y,w,h,l) {begin();}

}; // GNUI_Pack class

#endif
