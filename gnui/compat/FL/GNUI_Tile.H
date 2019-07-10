#ifndef GNUI_Tile_H
#define GNUI_Tile_H

#include "GNUI_Widget.H"
#include <gnui/TiledGroup.h>

class GNUI_Tile : public gnui::TiledGroup {

public:
  GNUI_Tile(int x, int y, int w, int h, const char*l = 0)
    : gnui::TiledGroup(x,y,w,h,l) {begin();}
};

#endif

