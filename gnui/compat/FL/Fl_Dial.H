#ifndef Fl_Dial_H
#define Fl_Dial_H

#include "Fl_Widget.H"
#include <gnui/Dial.h>
typedef gnui::Dial Fl_Dial;

enum {
  FL_NORMAL_DIAL	= gnui::Dial::NORMAL,
  FL_LINE_DIAL		= gnui::Dial::LINE,
  FL_FILL_DIAL		= gnui::Dial::FILL
};

#endif

