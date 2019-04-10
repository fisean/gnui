#ifndef FL_gl_H
#define FL_gl_H

#include <fltk/gl.h>

#define gl_start	gnui::glstart
#define	gl_finish	gnui::glfinish
#define gl_color	gnui::glsetcolor
#define	gl_rect		gnui::glstrokerect
#define gl_rectf	gnui::glfillrect
#define gl_font		gnui::glsetfont
inline float gl_height() {return gnui::glgetascent()+gnui::glgetdescent();}
#define gl_descent	gnui::glgetdescent
#define gl_width	gnui::glgetwidth
#define gl_draw		gnui::gldrawtext
//void gl_measure(const char*, int& x, int& y);
#define gl_draw_image	gnui::gldrawimage

#endif // !FL_gl_H
