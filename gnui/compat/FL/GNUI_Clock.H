#ifndef GNUI_Clock_H
#define GNUI_Clock_H

#include "GNUI_Widget.H"
#include <gnui/Clock.h>

typedef gnui::ClockOutput GNUI_Clock_Output;
typedef gnui::Clock GNUI_Clock;

enum {
  GNUI_SQUARE_CLOCK	= gnui::Clock::SQUARE,
  GNUI_ROUND_CLOCK	= gnui::Clock::ROUND,
  GNUI_ANALOG_CLOCK	= gnui::Clock::SQUARE,
  GNUI_DIGITAL_CLOCK	= gnui::Clock::DIGITAL // nyi
};

#endif

