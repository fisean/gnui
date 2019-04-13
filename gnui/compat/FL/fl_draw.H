#ifndef fl_draw_H
#define fl_draw_H

#include "Enumerations.H"
#include <gnui/draw.h>
#include <gnui/Font.h>

inline void fl_color(gnui::Color c) {gnui::setcolor(c);}
inline void fl_color(uchar r, uchar g, uchar b) {gnui::setcolor(gnui::color(r,g,b));}
inline gnui::Color fl_color() {return gnui::getcolor();}

// clip:
inline void fl_push_clip(int x, int y, int w, int h) {gnui::push_clip(x,y,w,h);}
inline void fl_push_no_clip() {gnui::push_no_clip();}
#define fl_clip		fl_push_clip
#define fl_pop_clip	gnui::pop_clip
inline int fl_not_clipped(int x, int y, int w, int h) {return gnui::not_clipped(gnui::Rectangle(x,y,w,h));}
inline int fl_clip_box(int X, int Y, int W, int H, int& x, int& y, int& w, int& h) {
  gnui::Rectangle r(X,Y,W,H);
  int i = intersect_with_clip(r);
  x = r.x(); y = r.y(); w = r.w(); h = r.h();
  return i;
}

// points:
inline void fl_point(int x, int y) {gnui::drawpoint(x,y);}

// line type:
#define fl_line_style	gnui::line_style
enum {
  FL_SOLID	= gnui::SOLID,
  FL_DASH	= gnui::DASH,
  FL_DOT	= gnui::DOT,
  FL_DASHDOT	= gnui::DASHDOT,
  FL_DASHDOTDOT	= gnui::DASHDOTDOT,
  FL_CAP_FLAT	= gnui::CAP_FLAT,
  FL_CAP_ROUND	= gnui::CAP_ROUND,
  FL_CAP_SQUARE	= gnui::CAP_SQUARE,
  FL_JOIN_MITER	= gnui::JOIN_MITER,
  FL_JOIN_ROUND	= gnui::JOIN_ROUND,
  FL_JOIN_BEVEL	= gnui::JOIN_BEVEL
};

// rectangles tweaked to exactly fill the pixel rectangle:
inline void fl_rect(int x, int y, int w, int h) {gnui::strokerect(gnui::Rectangle(x,y,w,h));}
inline void fl_rect(int x, int y, int w, int h, gnui::Color c) {gnui::setcolor(c); gnui::strokerect(gnui::Rectangle(x,y,w,h));}
inline void fl_rectf(int x, int y, int w, int h) {gnui::fillrect(gnui::Rectangle(x,y,w,h));}
inline void fl_rectf(int x, int y, int w, int h, gnui::Color c) {gnui::setcolor(c); gnui::fillrect(gnui::Rectangle(x,y,w,h));}

// line segments:
inline void fl_line(int x0,int y0, int x1,int y1) {gnui::drawline(x0,y0,x1,y1);}
inline void fl_line(int x0,int y0, int x1,int y1, int x2,int y2) {
  gnui::addvertex(x0,y0);
  gnui::addvertex(x1,y1);
  gnui::addvertex(x2,y2);
  gnui::strokepath();
}

// closed line segments:
inline void fl_loop(int x0,int y0, int x1,int y1, int x2,int y2) {
  gnui::addvertex(x0,y0);
  gnui::addvertex(x1,y1);
  gnui::addvertex(x2,y2);
  gnui::closepath();
  gnui::strokepath();
}
inline void fl_loop(int x0,int y0, int x1,int y1, int x2,int y2, int x3,int y3) {
  gnui::addvertex(x0,y0);
  gnui::addvertex(x1,y1);
  gnui::addvertex(x2,y2);
  gnui::addvertex(x3,y3);
  gnui::closepath();
  gnui::strokepath();
}

// filled polygons
inline void fl_polygon(int x0,int y0, int x1,int y1, int x2,int y2) {
  gnui::addvertex(x0,y0);
  gnui::addvertex(x1,y1);
  gnui::addvertex(x2,y2);
  gnui::closepath();
  gnui::fillpath();
}
inline void fl_polygon(int x0,int y0, int x1,int y1, int x2,int y2, int x3,int y3) {
  gnui::addvertex(x0,y0);
  gnui::addvertex(x1,y1);
  gnui::addvertex(x2,y2);
  gnui::addvertex(x3,y3);
  gnui::closepath();
  gnui::fillpath();
}

// draw rectilinear lines, horizontal segment first:
inline void fl_xyline(int x, int y, int x1) {
  gnui::drawline(x,y,x1,y);
}
inline void fl_xyline(int x, int y, int x1, int y2) {
  gnui::addvertex(x,y);
  gnui::addvertex(x1,y);
  gnui::addvertex(x1,y2);
  gnui::strokepath();
}
inline void fl_xyline(int x, int y, int x1, int y2, int x3) {
  gnui::addvertex(x,y);
  gnui::addvertex(x1,y);
  gnui::addvertex(x1,y2);
  gnui::addvertex(x3,y2);
  gnui::strokepath();
}

// draw rectilinear lines, vertical segment first:
inline void fl_yxline(int x, int y, int y1) {
  gnui::drawline(x,y,x,y1);
}
inline void fl_yxline(int x, int y, int y1, int x2) {
  gnui::addvertex(x,y);
  gnui::addvertex(x,y1);
  gnui::addvertex(x2,y1);
  gnui::strokepath();
}
inline void fl_yxline(int x, int y, int y1, int x2, int y3) {
  gnui::addvertex(x,y);
  gnui::addvertex(x,y1);
  gnui::addvertex(x2,y1);
  gnui::addvertex(x2,y3);
  gnui::strokepath();
}

inline void fl_arc(int x,int y,int w,int h,float a,float a2) {gnui::addchord(gnui::Rectangle(x,y,w,h),a,a2); gnui::strokepath();}
inline void fl_pie(int x,int y,int w,int h,float a,float a2) {gnui::addpie(gnui::Rectangle(x,y,w,h),a,a2); gnui::fillpath();}
inline void fl_chord(int x,int y,int w,int h,float a,float a2) {gnui::addchord(gnui::Rectangle(x,y,w,h),a,a2); gnui::fillpath();}

// scalable drawing code (code in fl_vertex.C and fl_arc.C):
#define fl_push_matrix	gnui::push_matrix
#define fl_pop_matrix	gnui::pop_matrix
#define fl_scale	gnui::scale
#define fl_translate	gnui::translate
#define fl_rotate	gnui::rotate
#define fl_mult_matrix	gnui::concat
#define fl_begin_points	gnui::newpath
#define fl_begin_line	gnui::newpath
#define fl_begin_loop	gnui::newpath
#define fl_begin_polygon gnui::newpath
#define fl_vertex	gnui::addvertex
#define fl_curve	gnui::addcurve
inline void fl_arc(float x,float y,float r, float a1, float a2) {gnui::addarc(x-r,y-r,2*r,2*r,a1,a2);}
#define fl_circle	gnui::addcircle
#define fl_end_points	gnui::drawpoints
#define fl_end_line	gnui::strokepath
inline void fl_end_loop() {gnui::closepath();gnui::strokepath();}
#define fl_end_polygon	gnui::fillpath
#define fl_begin_complex_polygon gnui::newpath
#define fl_gap		gnui::closepath
#define fl_end_complex_polygon	gnui::fillpath

// current font: (size was an int in gnui1.1)
inline void fl_font(gnui::Font* f, float size) {gnui::setfont(f,size);}
inline void fl_font(int f, float size) {gnui::setfont(gnui::font(f),size);}
inline gnui::Font* fl_font() {return gnui::getfont();}
inline float fl_size() {return gnui::getsize();}

// information you can get about the current font:
inline float fl_height() {return gnui::getascent()+gnui::getdescent();}
inline float fl_height(int, float size) {return size;}
inline float fl_descent() {return gnui::getdescent();}
inline float fl_width(const char* c) {return gnui::getwidth(c);}
inline float fl_width(const char* c, int n) {return gnui::getwidth(c,n);}
inline float fl_width(char c) {return gnui::getwidth(&c,1);}

// draw using current font:
inline void fl_draw(const char* s, int x, int y) {gnui::drawtext(s,x,y);}
inline void fl_draw(const char* s, int n, int x, int y) {gnui::drawtext(s,n,x,y);}
inline void fl_measure(const char* s, int& x, int& y) {gnui::measure(s,x,y);}
inline void fl_draw(const char* s, int x,int y,int w,int h, gnui::Flags f) {gnui::drawtext(s,gnui::Rectangle(x,y,w,h),f);}

// boxtypes:
//void fl_frame(const char* s, int x, int y, int w, int h);
//void fl_frame2(const char* s, int x, int y, int w, int h);
// This no longer works because boxes take a style, not a color:
//  #include <gnui/Box.h>
//  inline void fl_draw_box(gnui::Box* b, int x, int y, int w, int h, gnui::Color c) {b->draw(x,y,w,h,c);}

// images:
static inline gnui::PixelType fromdelta(int d) {return d==1?gnui::MONO:d==3?gnui::RGB:gnui::RGBx;}
inline void fl_draw_image(const uchar* p, int x,int y,int w,int h, int delta, int ldelta) {gnui::drawimage(p,fromdelta(delta),gnui::Rectangle(x,y,w,h),ldelta);}
inline void fl_draw_image(const uchar* p, int x,int y,int w,int h, int delta) {gnui::drawimage(p,fromdelta(delta),gnui::Rectangle(x,y,w,h));}

inline void fl_draw_image_mono(const uchar* p, int x,int y,int w,int h, int delta, int ldelta) {gnui::drawimage(p,gnui::MONO,gnui::Rectangle(x,y,w,h),ldelta);}
inline void fl_draw_image_mono(const uchar* p, int x,int y,int w,int h, int delta=1) {gnui::drawimage(p,gnui::MONO,gnui::Rectangle(x,y,w,h));}

typedef gnui::DrawImageCallback Fl_Draw_Image_Cb;
inline void fl_draw_image(Fl_Draw_Image_Cb cb, void* p, int x,int y,int w,int h, int delta=3) {gnui::drawimage(cb,p,fromdelta(delta),gnui::Rectangle(x,y,w,h));}
inline void fl_draw_image_mono(Fl_Draw_Image_Cb cb, void* p, int x,int y,int w,int h, int delta=1) {gnui::drawimage(cb,p,gnui::MONO,gnui::Rectangle(x,y,w,h));}

inline uchar *fl_read_image(uchar *p, int x,int y, int w, int h, int alpha=0) {return gnui::readimage(p, alpha?gnui::RGBA:gnui::RGB, gnui::Rectangle(x,y,w,h));}

inline void fl_rectf(int x, int y, int w, int h, uchar r, uchar g, uchar b) {gnui::setcolor(gnui::color(r,g,b)); gnui::fillrect(gnui::Rectangle(x,y,w,h));}

#define fl_draw_pixmap		gnui::draw_xpm
#define fl_measure_pixmap	gnui::measure_xpm
#define fl_scroll		gnui::scrollrect
#define fl_shortcut_label	gnui::key_name
#define fl_overlay_rect		gnui::overlay_rect
#define fl_overlay_clear	gnui::overlay_clear
#define fl_draw_symbol		gnui::draw_symbol
#define fl_add_symbol		gnui::add_symbol
#define fl_frame		gnui::drawframe2
#define fl_frame2		gnui::drawframe

#endif

//
// End of "$Id$".
//
