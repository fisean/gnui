#ifndef GNUI_Widget_H
#define GNUI_Widget_H

#include "Enumerations.H"
#define FLTK_1_WIDGET 1
#include <gnui/Widget.h>

typedef gnui::Widget GNUI_Widget;

typedef gnui::Callback GNUI_Callback;
typedef GNUI_Callback* GNUI_Callback_p; // needed for BORLAND
typedef gnui::Callback0 GNUI_Callback0;
typedef gnui::Callback1 GNUI_Callback1;

enum {
  GNUI_RESERVED_TYPE 	= gnui::Widget::RESERVED_TYPE
};

#endif
