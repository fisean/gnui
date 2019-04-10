// This emulation header was designed to get flwm to compile. It
// probably does not work for any other x fltk program.

#ifndef Fl_X_H
#define Fl_X_H

#include "Enumerations.H"
#include <fltk/x.h>

#define Fl_X		gnui::CreatedWindow
#define fl_display	gnui::xdisplay
#define fl_screen	gnui::xscreen
#define fl_xevent	(&gnui::xevent)
#define fl_colormap	gnui::xcolormap
#define fl_open_display	gnui::open_display
#define fl_visual	gnui::xvisual
#define fl_xid(w)	gnui::xid(w)
#define fl_event_time	gnui::event_time
#define fl_xpixel(x)	gnui::xpixel(x)
#define fl_window	gnui::xwindow
#define fl_gc		gnui::gc
#define fl_xfont	gnui::xfont()

#endif
