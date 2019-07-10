#ifndef GNUI_Button_H
#define GNUI_Button_H

#include "GNUI_Widget.H"
#include <gnui/Button.h>
typedef gnui::Button GNUI_Button;

enum {
  GNUI_NORMAL_BUTTON	= 0,
  GNUI_TOGGLE_BUTTON	= gnui::Button::TOGGLE,
  GNUI_RADIO_BUTTON	= gnui::Button::RADIO,
  GNUI_HIDDEN_BUTTON	= gnui::Button::HIDDEN // may not work in 2.0
};

#endif

