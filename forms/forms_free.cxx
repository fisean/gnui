//
// "$Id$"
//
// Forms free widget routines for the Fast Light Tool Kit (FLTK).
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

// Emulation of the Forms "free" widget.
// This emulation allows the free demo to run, and has allowed
// me to port several other programs, but it is in no way
// complete.

#include <fltk/Fl.h>
#include <fltk/GNUI_Free.h>

void GNUI_Free::step(void *v) {
  GNUI_Free *f = (GNUI_Free *)v;
  f->handle(GNUI_STEP);
  Fl::add_timeout(.01,step,v);
}

GNUI_Free::GNUI_Free(uchar t,int x,int y,int w,int h,const char *l,
		 GNUI_HANDLEPTR hdl) :
GNUI_Widget(x,y,w,h,l) {
  type(t);
  hfunc = hdl;
  if (t == GNUI_SLEEPING_FREE) set_flag(GNUI_INACTIVE);
  if (t == GNUI_CONTINUOUS_FREE || t == GNUI_ALL_FREE)
    Fl::add_timeout(.01,step,this);
}

GNUI_Free::~GNUI_Free() {
  Fl::remove_timeout(step,this);
  hfunc(this,GNUI_FREEMEM,0,0,0);
}

void GNUI_Free::draw() {hfunc(this,GNUI_DRAW,0,0,0);}

int GNUI_Free::handle(int e) {
  char key = Fl::event_key();
  switch (e) {
  case GNUI_FOCUS:
    if (type()!=GNUI_INPUT_FREE && type()!=GNUI_ALL_FREE) return 0;
    break;
  case GNUI_PUSH:
  case GNUI_DRAG:
  case GNUI_RELEASE:
    key = 4-Fl::event_button();
    break;
  case GNUI_SHORTCUT:
    return 0;
  }
  if (hfunc(this, e, float(Fl::event_x()), float(Fl::event_y()), key)) do_callback();
  return 1;
}

//
// End of "$Id$".
//
