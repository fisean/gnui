#ifndef GNUI_Scrollbar_H
#define GNUI_Scrollbar_H

#include "GNUI_Slider.H"
#include <gnui/Scrollbar.h>

class GNUI_Scrollbar : public gnui::Scrollbar {
public:
  GNUI_Scrollbar(int x, int y, int w, int h, const char*l = 0)
    : gnui::Scrollbar(x,y,w,h,l) {set_vertical();}
};

#endif
