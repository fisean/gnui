#ifndef Fl_Scrollbar_H
#define Fl_Scrollbar_H

#include "Fl_Slider.H"
#include <gnui/Scrollbar.h>

class Fl_Scrollbar : public gnui::Scrollbar {
public:
  Fl_Scrollbar(int x, int y, int w, int h, const char*l = 0)
    : gnui::Scrollbar(x,y,w,h,l) {set_vertical();}
};

#endif
