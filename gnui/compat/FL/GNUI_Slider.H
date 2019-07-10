#ifndef GNUI_Slider_H
#define GNUI_Slider_H

#include "GNUI_Widget.H"
#define FLTK_1_SLIDER 1
#include <gnui/Slider.h>

class GNUI_Slider : public gnui::Slider {
public:
  GNUI_Slider(int x, int y, int w, int h, const char*l = 0)
    : gnui::Slider(x,y,w,h,l) {set_vertical();}
};

enum {
  GNUI_VERT_SLIDER	= gnui::Slider::LINEAR,
  GNUI_HOR_SLIDER		= gnui::Slider::HORIZONTAL,
  GNUI_VERT_FILL_SLIDER	= gnui::Slider::FILL,
  GNUI_HOR_FILL_SLIDER	= gnui::Slider::HORIZONTAL+gnui::Slider::FILL,
  GNUI_VERT_NICE_SLIDER	= gnui::Slider::LINEAR,
  GNUI_HOR_NICE_SLIDER	= gnui::Slider::HORIZONTAL
};

#endif

