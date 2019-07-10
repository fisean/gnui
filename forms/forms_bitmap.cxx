//
// "$Id$"
//
// Forms compatible bitmap function for the Fast Light Tool Kit (FLTK).
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
//    http://www.fltk.org/str.php
//

#include <fltk/forms.h>

GNUI_FormsBitmap::GNUI_FormsBitmap(
  GNUI_Boxtype t, int x, int y, int w, int h, const char* l)
: GNUI_Widget(x, y, w, h, l) {
  box(t);
  b = 0;
  color(GNUI_BLACK);
  clear_flag(GNUI_ALIGN_MASK);
  set_flag(GNUI_ALIGN_BOTTOM);
}

void GNUI_FormsBitmap::set(int W, int H, const uchar *bits) {
  delete b;
  bitmap(new GNUI_Bitmap(bits, W, H));
}

void GNUI_FormsBitmap::draw() {
  box()->draw(0, 0, w(), h(), selection_color());
  if (b) {
    gnui_color(color());
    b->draw((w()-b->width())/2, (h()-b->height())/2);
  }
  draw_inside_label();
}

//
// End of "$Id$".
//
