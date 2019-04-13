#ifndef Fl_Tile_H
#define Fl_Tile_H

#include "Fl_Widget.H"
#include <gnui/TiledGroup.h>

class Fl_Tile : public gnui::TiledGroup {

public:
  Fl_Tile(int x, int y, int w, int h, const char*l = 0)
    : gnui::TiledGroup(x,y,w,h,l) {begin();}
};

#endif

