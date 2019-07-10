// This emulation header was designed to get flwm to compile. It
// probably does not work for any other x gnui program.

#ifndef GNUI_X_H
#define GNUI_X_H

#include "Enumerations.H"
#include <gnui/x.h>

#define GNUI_X		gnui::CreatedWindow
#define gnui_display	gnui::xdisplay
#define gnui_screen	gnui::xscreen
#define gnui_xevent	(&gnui::xevent)
#define gnui_colormap	gnui::xcolormap
#define gnui_open_display	gnui::open_display
#define gnui_visual	gnui::xvisual
#define gnui_xid(w)	gnui::xid(w)
#define gnui_event_time	gnui::event_time
#define gnui_xpixel(x)	gnui::xpixel(x)
#define gnui_window	gnui::xwindow
#define gnui_gc		gnui::gc
#define gnui_xfont	gnui::xfont()

#endif
