#ifndef Fl_Input_H
#define Fl_Input_H

#include "Fl_Widget.H"
#include <gnui/Input.h>
class Fl_Input : public gnui::Input {
public:
  Fl_Input(int x, int y, int w, int h, const char* l=0) : gnui::Input(x,y,w,h,l) {}
  int wrap() const { return type() == gnui::Input::WORDWRAP; }
  void wrap(int b) { type(b ? gnui::Input::WORDWRAP : gnui::Input::MULTILINE);}
};

enum {
  FL_NORMAL_INPUT	= gnui::Input::NORMAL,
  FL_FLOAT_INPUT	= 1, // probably needs the IntInput subclass!
  FL_INT_INPUT		= 2,
//FL_HIDDEN_INPUT	// not in gnui.0
  FL_MULTILINE_INPUT	= gnui::Input::MULTILINE,
  FL_SECRET_INPUT	= gnui::Input::SECRET,
//FL_INPUT_TYPE		= 7,
//FL_INPUT_READONLY	= 8,
  FL_INPUT_WRAP		= gnui::Input::WORDWRAP,
  FL_MULTILINE_INPUT_WRAP = gnui::Input::WORDWRAP
};

#endif

