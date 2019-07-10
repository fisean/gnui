#ifndef GNUI_Roller_H
#define GNUI_Roller_H

#include "GNUI_Valuator.H"
#include <gnui/ThumbWheel.h>

class GNUI_Roller : public gnui::ThumbWheel {
public:
  GNUI_Roller(int x, int y, int w, int h, const char*l = 0)
    : gnui::ThumbWheel(x,y,w,h,l) {set_vertical();}
};

#endif
