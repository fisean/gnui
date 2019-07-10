// "$Id$"
//
// Copyright 1998-2006 by Bill Spitzak and others.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.
//
// Please report all bugs and problems on the following page:
//
//    http://www.gnui.org/str.php

/*
  The FLTK drawing library, used by all widgets to draw themselves.

  These functions can only be called when FLTK is setup to draw
  things. This is only true:
  - Inside the Widget::draw() virtual function.
  - Inside the Symbol::draw() virtual function.
  - After calling Widget::make_current(), before calling wait() or flush().
  Calling the drawing functions at other times produces undefined results,
  including crashing.
*/

#ifndef gnui_draw_h
#define gnui_draw_h

#include "Flags.h" // for alignment values
#include "Color.h"
#include "Rectangle.h"
#include "PixelType.h"

namespace gnui {

/// \name gnui/draw.h
//@{

struct Font;
class Style;

class GNUI_API GSave {
  void* data[4]; // hopefully big enough for everybody...
 public:
  GSave();
  ~GSave();
};

// Transformation
GNUI_API void push_matrix();
GNUI_API void pop_matrix();
GNUI_API void scale(float x, float y);
GNUI_API void scale(float x);
GNUI_API void translate(float x, float y);
GNUI_API void translate(int x, int y);
GNUI_API void rotate(float d);
GNUI_API void concat(float, float, float, float, float, float);
GNUI_API void load_identity();

// get and use transformed positions:
GNUI_API void transform(float& x, float& y);
GNUI_API void transform_distance(float& x, float& y);
GNUI_API void transform(int& x, int& y);
GNUI_API void transform(const Rectangle& from, Rectangle& to);
GNUI_API void transform(int& x, int& y, int& w, int& h);

// Clipping
GNUI_API void push_clip(const Rectangle&);
//! Same as push_clip(Rectangle(x,y,w,h)) but faster:
GNUI_API void push_clip(int X,int Y, int W, int H);
GNUI_API void clipout(const Rectangle&);
GNUI_API void pop_clip();
GNUI_API void push_no_clip();
GNUI_API bool not_clipped(const Rectangle&);
GNUI_API int intersect_with_clip(Rectangle&);

GNUI_API void setcolor(Color);
GNUI_API void setcolor_alpha(Color, float alpha);
extern GNUI_API Color current_color_;
inline Color getcolor() {return current_color_;}

extern GNUI_API Color current_bgcolor_;
inline void setbgcolor(Color c) {current_bgcolor_ = c;}
inline Color getbgcolor() {return current_bgcolor_;}

extern GNUI_API const Style* drawstyle_;
void GNUI_API drawstyle(const Style* s, Flags);
inline const Style* drawstyle() {return drawstyle_;}

extern GNUI_API Flags drawflags_;
inline void setdrawflags(Flags f) {drawflags_ = f;}
inline Flags drawflags() {return drawflags_;}
inline Flags drawflags(Flags f) {return drawflags_ & f;}

// line type:
GNUI_API void line_style(int, float width=0, const char* dashes=0);
enum {
  SOLID	= 0,
  DASH	= 1,
  DOT	= 2,
  DASHDOT	= 3,
  DASHDOTDOT	= 4,

  CAP_FLAT	= 0x100,
  CAP_ROUND	= 0x200,
  CAP_SQUARE	= 0x300,

  JOIN_MITER	= 0x1000,
  JOIN_ROUND	= 0x2000,
  JOIN_BEVEL	= 0x3000
};
extern GNUI_API int line_style_;
inline GNUI_API int line_style() {return line_style_;}
extern GNUI_API float line_width_;
inline GNUI_API float line_width() {return line_width_;}
extern GNUI_API const char* line_dashes_;
inline GNUI_API const char* line_dashes() {return line_dashes_;}

// Path construction
GNUI_API void newpath();
GNUI_API void addvertex(float x, float y);
GNUI_API void addvertex(int x, int y);
GNUI_API void addvertices(int n, const float v[][2]);
GNUI_API void addvertices(int n, const int v[][2]);
GNUI_API void addvertices_transformed(int n, const float v[][2]);
GNUI_API void addcurve(float,float, float,float, float,float, float,float);
GNUI_API void addarc(float x,float y,float w,float h, float a1, float a2);
GNUI_API void addpie(const Rectangle& r, float a, float a2);
GNUI_API void addchord(const Rectangle& r,float a,float a2);
GNUI_API void closepath();

// Shapes and lines
GNUI_API void strokepath();
GNUI_API void fillpath();
GNUI_API void fillstrokepath(Color);

GNUI_API void fillrect(int, int, int, int);
inline void fillrect(const Rectangle& r) {fillrect(r.x(),r.y(),r.w(),r.h());}
GNUI_API void strokerect(int, int, int, int);
inline void strokerect(const Rectangle& r) {strokerect(r.x(),r.y(),r.w(),r.h());}
GNUI_API void drawline(int x0, int y0, int x1, int y1);
GNUI_API void drawline(float x0, float y0, float x1, float y1);
GNUI_API void drawpoint(int x, int y);
GNUI_API void drawpoint(float x, float y);

// Text
GNUI_API void setfont(Font*, float size);
GNUI_API void setfont(const char*, float size);
GNUI_API void setfont(const char*, int attributes, float size);

// change the encoding used to draw bytes (depreciated)
extern GNUI_API const char* encoding_;
inline const char* get_encoding() {return encoding_;}
GNUI_API void set_encoding(const char*);

// information you can get about the current font+size+encoding:
extern GNUI_API Font* current_font_;
extern GNUI_API float current_size_; // should be 2x2 transformation matrix
inline Font* getfont() {return current_font_;}
inline float getsize() {return current_size_;}

// measure things in the current font:
GNUI_API float getwidth(const char*);
GNUI_API float getwidth(const char*, int length);
GNUI_API float getascent();
GNUI_API float getdescent();

// draw using current font:
GNUI_API void drawtext_transformed(const char*, int n, float x, float y);
GNUI_API void drawtext(const char*, float x, float y);
GNUI_API void drawtext(const char*, int length, float x, float y);

// the label text formatter:
GNUI_API void measure(const char*, int& w, int& h, Flags = 0);
GNUI_API void measure(float (*getwidth)(const char*, int),const char*, float& w, float& h, Flags = 0);
GNUI_API void drawtext(const char*, const Rectangle&, Flags);
GNUI_API void drawtext(void (*textfunction)(const char*,int,float,float),
		     float (*getwidth)(const char*, int),
		     const char* str, const Rectangle& r, Flags flags);

// set where \t characters go in label text formatter:
extern GNUI_API const int* column_widths_;
inline const int* column_widths() {return column_widths_;}
inline void column_widths(const int* i) {column_widths_ = i;}
// see also Symbol.h for @-sign commands

// Images
GNUI_API void drawimage(const uchar*, PixelType, const Rectangle&);
GNUI_API void drawimage(const uchar*, PixelType, const Rectangle&, int linedelta);

typedef const uchar* (*DrawImageCallback)(void* data, int x, int y, int w, uchar* buffer);
GNUI_API void drawimage(DrawImageCallback, void*, PixelType, const Rectangle&);

GNUI_API uchar *readimage(uchar *p, PixelType, const Rectangle&);
GNUI_API uchar *readimage(uchar *p, PixelType, const Rectangle&, int linedelta);

GNUI_API void scrollrect(const Rectangle&, int dx, int dy,
		       void (*draw_area)(void*, const Rectangle&), void*);

#ifndef DOXYGEN /* depreciated: */
GNUI_API void drawframe(const char* s, int x, int y, int w, int h);
GNUI_API void drawframe2(const char* s, int x, int y, int w, int h);
GNUI_API void overlay_rect(int,int,int,int);
GNUI_API void overlay_clear();
#endif

//@}

}

#endif

//
// End of "$Id$".
//
