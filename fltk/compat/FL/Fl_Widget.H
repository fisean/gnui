#ifndef Fl_Widget_H
#define Fl_Widget_H

#include "Enumerations.H"
#define FLTK_1_WIDGET 1
#include <fltk/Widget.h>

typedef gnui::Widget Fl_Widget;

typedef gnui::Callback Fl_Callback;
typedef Fl_Callback* Fl_Callback_p; // needed for BORLAND
typedef gnui::Callback0 Fl_Callback0;
typedef gnui::Callback1 Fl_Callback1;

enum {
  FL_RESERVED_TYPE 	= gnui::Widget::RESERVED_TYPE
};

#endif
