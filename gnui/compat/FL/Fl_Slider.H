#ifndef Fl_Slider_H
#define Fl_Slider_H

#include "Fl_Widget.H"
#define FLTK_1_SLIDER 1
#include <gnui/Slider.h>

class Fl_Slider : public gnui::Slider {
public:
  Fl_Slider(int x, int y, int w, int h, const char*l = 0)
    : gnui::Slider(x,y,w,h,l) {set_vertical();}
};

enum {
  FL_VERT_SLIDER	= gnui::Slider::LINEAR,
  FL_HOR_SLIDER		= gnui::Slider::HORIZONTAL,
  FL_VERT_FILL_SLIDER	= gnui::Slider::FILL,
  FL_HOR_FILL_SLIDER	= gnui::Slider::HORIZONTAL+gnui::Slider::FILL,
  FL_VERT_NICE_SLIDER	= gnui::Slider::LINEAR,
  FL_HOR_NICE_SLIDER	= gnui::Slider::HORIZONTAL
};

#endif

