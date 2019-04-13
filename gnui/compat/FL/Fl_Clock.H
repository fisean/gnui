#ifndef Fl_Clock_H
#define Fl_Clock_H

#include "Fl_Widget.H"
#include <gnui/Clock.h>

typedef gnui::ClockOutput Fl_Clock_Output;
typedef gnui::Clock Fl_Clock;

enum {
  FL_SQUARE_CLOCK	= gnui::Clock::SQUARE,
  FL_ROUND_CLOCK	= gnui::Clock::ROUND,
  FL_ANALOG_CLOCK	= gnui::Clock::SQUARE,
  FL_DIGITAL_CLOCK	= gnui::Clock::DIGITAL // nyi
};

#endif

