// "$Id$"
//
// Font selection code for the Fast Light Tool Kit (FLTK).
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

#include <config.h>
#include <gnui/Font.h>
#include <gnui/draw.h>
#include <gnui/x.h>
#include <gnui/string.h>

/** \class gnui::Font

Identifies a font. You can create these with gnui::font(name) or
with gnui::list_fonts(). Do not attempt to create your instances
or modify it.

This is a struct so that gnui can initialize a table internally
with constants. Don't use the undocumented fields.
*/

/** \fn gnui::Font* gnui::Font::plus(int attributes);
  Return a font from the same family with the extra attributes turned
  on. This may return the same font if the attributes are already on
  or there is no font with those attributes.
*/

/** \fn gnui::Font* gnui::Font::bold()
  Same as plus(BOLD), returns a bold version of this font.
*/

/** \fn gnui::Font* gnui::Font::italic()
  Same as plus(ITALIC), returns an italic version of this font.
*/

/** \fn const char* gnui::Font::system_name();
  Returns the string actually passed to the operating system, which
  may be different than name().
  For Xlib this is a pattern sent to XListFonts to find all the sizes.
  For most other systems this is the same as name() without any attributes.
*/

/** \fn void gnui::drawtext_transformed(const char *text, int n, float x, float y);
  Draw text starting at a point returned by gnui::transform(). This
  is needed for complex text layout when the current transform may
  not match the transform being used by the font.
*/

/*! \fn void gnui::setfont(gnui::Font* font, float psize);

  Set the current font and font scaling so the size is size
  pixels. The size is unaffected by the current transformation matrix
  (you may be able to use gnui::transform() to get the size to get a
  properly scaled font).

  The size is given in pixels. Many pieces of software express sizes
  in "points" (for mysterious reasons, since everything else is
  measured in pixels!). To convert these point sizes to pixel sizes
  use the following code:
\code
const gnui::Monitor& monitor = gnui::Monitor::all();
float pixels_per_point = monitor.dpi_y()/72.0;
float font_pixel_size = font_point_size*pixels_per_point;
\endcode

  See the gnui::Font class for a description of what can be passed as
  a font. For most uses one of the built-in constant fonts like
  gnui::HELVETICA can be used.

*/

// Static variables containing the currently selected font, size, encoding:
gnui::Font* gnui::current_font_;
float gnui::current_size_;
const char *gnui::encoding_ = "iso10646-1";

#if USE_X11
# include "x11/Font.cxx"
#elif defined(_WIN32)
# include "win32/Font.cxx"
#elif USE_QUARTZ
# include "osx/Font.cxx"
#else
#error
#endif

/** \fn Font* gnui::getfont()
  Return the Font sent to the last setfont().
*/

/** \fn float gnui::getsize()
  Return the size sent to the last setfont(). You should use this as a
  minimum line spacing (using ascent()+descent() will produce oddly
  spaced lines for many fonts).
*/

/** \fn float gnui::getascent()
  Return the distance from the baseline to the top of letters in
  the current font.
*/

/** \fn float gnui::getdescent()
  Return the distance from the baseline to the bottom of letters in
  the current font.
*/

/** Draw a nul-terminated string. */
void gnui::drawtext(const char* text, float x, float y) {
  drawtext(text, strlen(text), x, y);
}

/**
  Draw the first n \e bytes (not characters if utf8 is used) starting
  at the given position.
*/
void gnui::drawtext(const char* text, int n, float x, float y) {
  transform(x,y);
  drawtext_transformed(text, n, x, y);
}

/** \fn float gnui::getwidth(const char *text, int n)
  Return the width of the first \a n bytes of this UTF-8 string drawn
  in the font set by the most recent setfont().
*/

/**
  Return the width of a nul-terminated UTF-8 string drawn in the
  font set by the most recent setfont().
*/
float gnui::getwidth(const char* text) {
  return getwidth(text, strlen(text));
}

/** \fn const char* gnui::Font::name(int* attributes)
  Return a string name for this font, and put any attributes
  (BOLD, ITALIC) into the location pointed to by \a attributes.
  Using the returned string and attributes as arguments to find()
  will return the same font.
*/

/**
  Return a single string that names this font. Passing this
  string and zero for the attributes to find() will return the
  same font.

  If the font's attributes are non-zero, this is done by appending a
  space and "Bold" and/or "Italic" to the name. This allows a single
  string rather than a string+attribute pair to identify a font, which
  is really useful for saving them in a file. <i>The return value is
  in a temporary buffer that will be overwritten on the next call in
  this case.</i>
*/
const char* gnui::Font::name() const {
  if (!attributes_) return name_;
  const int length=128;
  static char *buffer; if (!buffer) buffer = new char[length];
  strlcpy(buffer, name_, length);
  if (attributes_ & BOLD) strlcat(buffer, " Bold", length);
  if (attributes_ & ITALIC) strlcat(buffer, " Italic", length);
  return buffer;
}

/**
  Obsolete function to encourage FLTK to choose a 256-glyph font with
  the given encoding. You must call setfont() after changing this for
  it to have any effect.

  Notice that this is obsolete! Only the non-Xft X version actually
  uses it and that may be eliminated as well. In addition FLTK uses
  UTF-8 internally, and assummes that any font it prints with is
  using Unicode encoding (or ISO-8859-1 if there are only 256 characters).

  The default is "iso10646-1"
*/
void gnui::set_encoding(const char* f) {encoding_ = f;}

/** \fn const char* gnui::get_encoding()
  Returns the string sent to the most recent set_encoding().
*/

//
// End of "$Id$".
//
