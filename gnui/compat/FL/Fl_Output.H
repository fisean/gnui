#ifndef Fl_Output_H
#define Fl_Output_H

#include "Fl_Input.H"
#include <gnui/Output.h>
typedef gnui::Output Fl_Output;

enum {
  FL_NORMAL_OUTPUT	= gnui::Input::NORMAL,
  FL_MULTILINE_OUTPUT	= gnui::Input::MULTILINE,
  FL_MULTILINE_OUTPUT_WRAP = gnui::Input::WORDWRAP
};

#endif

