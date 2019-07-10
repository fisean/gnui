#ifndef GNUI_Value_Slider_H
#define GNUI_Value_Slider_H

#include "GNUI_Slider.H"
#include <gnui/ValueSlider.h>

class GNUI_Value_Slider : public gnui::ValueSlider {
public:
  GNUI_Value_Slider(int x, int y, int w, int h, const char*l = 0)
    : gnui::ValueSlider(x,y,w,h,l) {set_vertical();}
};

#endif

