#ifndef Fl_Roller_H
#define Fl_Roller_H

#include "Fl_Valuator.H"
#include <gnui/ThumbWheel.h>

class Fl_Roller : public gnui::ThumbWheel {
public:
  Fl_Roller(int x, int y, int w, int h, const char*l = 0)
    : gnui::ThumbWheel(x,y,w,h,l) {set_vertical();}
};

#endif
