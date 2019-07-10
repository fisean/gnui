//
// "$Id$"
//
// Forms timer object for the Fast Light Tool Kit (FLTK).
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

// Emulate the Forms Timer object
// You don't want to use this if you just want a timeout, call
// Fl::add_timeout directly!

#include <fltk/Fl.h>
#include <fltk/GNUI_Timer.h>
#include <fltk/gnui_draw.h>
#ifdef _WIN32
# include <sys/types.h> 
# include <sys/timeb.h>
#else
# include <sys/time.h>
#endif
#include <stdio.h>

#define GNUI_TIMER_BLINKRATE	0.2

void gnui_gettime(long* sec, long* usec) {
#ifdef _WIN32
  struct timeb tp;
  ftime(&tp);
  *sec = tp.time;
  *usec = tp.millitm * 1000;
#else
  struct timeval tp;
  struct timezone tzp;
  gettimeofday(&tp, &tzp);
  *sec = tp.tv_sec;
  *usec = tp.tv_usec;
#endif
}

void GNUI_Timer::draw() {
  int tt;
  char str[32];
  GNUI_Color color;
  if (on && delay<=0.0 && ((int) (delay / GNUI_TIMER_BLINKRATE) % 2))
    color = selection_color();
  else
    color = this->color();
  box()->draw(0, 0, w(), h(), color);
  if (type() == GNUI_VALUE_TIMER && delay>0.0) {
    double d = direction_ ? total-delay : delay;
    if (d < 60.0)
      sprintf(str, "%.1f", d);
    else {
      tt = (int) ((d+0.05) / 60.0);
      sprintf(str, "%d:%04.1f", tt, d - 60.0 * tt);
    }
    gnui_font(label_font(), label_size());
    gnui_color(label_color());
    gnui_draw(str, 0, 0, w(), h(), GNUI_ALIGN_CENTER);
  } else
    draw_inside_label();
}

void GNUI_Timer::stepcb(void* v) {
  ((GNUI_Timer*)v)->step();
}

void GNUI_Timer::step() {
  if (!on) return;
  double lastdelay = delay;
  long sec, usec; gnui_gettime(&sec, &usec);
  delay -= (double) (sec - lastsec) + (double) (usec - lastusec) / 1000000.0;
  lastsec = sec; lastusec = usec;
  if (lastdelay > 0.0 && delay <= 0.0) {
    if (type() == GNUI_HIDDEN_TIMER) {
      on = 0;
      delay = 0;
    } else {
      redraw();
      Fl::add_timeout(GNUI_TIMER_BLINKRATE, (GNUI_Timeout_Handler)stepcb, this);
    }
    do_callback();
  } else {
    if (type() == GNUI_VALUE_TIMER) redraw();
    Fl::add_timeout(GNUI_TIMER_BLINKRATE, (GNUI_Timeout_Handler)stepcb, this);
  }
}

int GNUI_Timer::handle(int event) {
  if (event == GNUI_RELEASE && delay <= 0) value(0.0);
  return 0;
}

GNUI_Timer::~GNUI_Timer() {
  Fl::remove_timeout((GNUI_Timeout_Handler)stepcb, this);
}

GNUI_Timer::GNUI_Timer(uchar t, int x, int y, int w, int h, const char* l)
: GNUI_Widget(x, y, w, h, l) {
  box(GNUI_DOWN_BOX);
  selection_color(GNUI_RED);
  delay = 0;
  on = 0;
  direction_ = 0;
  type(t);
  if (t == GNUI_HIDDEN_TIMER) clear_visible();
  if (t == GNUI_VALUE_TIMER) {
	  clear_flag(GNUI_ALIGN_MASK);
	  set_flag(GNUI_ALIGN_LEFT);
  }
}

void GNUI_Timer::value(double d) {
  delay = total = d;
  on = (d > 0.0);
  gnui_gettime(&(lastsec), &(lastusec));
  if (type() != GNUI_HIDDEN_TIMER) redraw();
  Fl::remove_timeout((GNUI_Timeout_Handler)stepcb, this);
  if (on) Fl::add_timeout(GNUI_TIMER_BLINKRATE, (GNUI_Timeout_Handler)stepcb, this);
}

void GNUI_Timer::suspended(char d) {
  if (!d) {
    if (on) return;
    on = (delay > 0.0);
    gnui_gettime(&(lastsec), &(lastusec));
    if (on) Fl::add_timeout(GNUI_TIMER_BLINKRATE, (GNUI_Timeout_Handler)stepcb, this);
  } else {
    if (!on) return;
    on = 0;
    Fl::remove_timeout((GNUI_Timeout_Handler)stepcb, this);
  }
}

//
// End of "$Id$".
//
