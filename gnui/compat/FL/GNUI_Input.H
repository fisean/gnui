#ifndef GNUI_Input_H
#define GNUI_Input_H

#include "GNUI_Widget.H"
#include <gnui/Input.h>
class GNUI_Input : public gnui::Input {
public:
  GNUI_Input(int x, int y, int w, int h, const char* l=0) : gnui::Input(x,y,w,h,l) {}
  int wrap() const { return type() == gnui::Input::WORDWRAP; }
  void wrap(int b) { type(b ? gnui::Input::WORDWRAP : gnui::Input::MULTILINE);}
};

enum {
  GNUI_NORMAL_INPUT	= gnui::Input::NORMAL,
  GNUI_FLOAT_INPUT	= 1, // probably needs the IntInput subclass!
  GNUI_INT_INPUT		= 2,
//GNUI_HIDDEN_INPUT	// not in gnui.0
  GNUI_MULTILINE_INPUT	= gnui::Input::MULTILINE,
  GNUI_SECRET_INPUT	= gnui::Input::SECRET,
//GNUI_INPUT_TYPE		= 7,
//GNUI_INPUT_READONLY	= 8,
  GNUI_INPUT_WRAP		= gnui::Input::WORDWRAP,
  GNUI_MULTILINE_INPUT_WRAP = gnui::Input::WORDWRAP
};

#endif

