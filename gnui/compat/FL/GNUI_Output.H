#ifndef GNUI_Output_H
#define GNUI_Output_H

#include "GNUI_Input.H"
#include <gnui/Output.h>
typedef gnui::Output GNUI_Output;

enum {
  GNUI_NORMAL_OUTPUT	= gnui::Input::NORMAL,
  GNUI_MULTILINE_OUTPUT	= gnui::Input::MULTILINE,
  GNUI_MULTILINE_OUTPUT_WRAP = gnui::Input::WORDWRAP
};

#endif

