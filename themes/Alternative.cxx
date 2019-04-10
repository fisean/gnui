//
// "$Id$"
//
// Theme plugin file for FLTK
//
// Copyright 1999 Bill Spitzak and others.
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

#include <fltk/Box.h>
#include <fltk/Style.h>
#include <fltk/Widget.h>
#include <fltk/Button.h>
#include <fltk/draw.h>

// a couple of of new boxtypes (look familiar?)
static const gnui::FrameBox
alt_thick_down_box(0, "NNUUJJXXAAAA");

static const gnui::FrameBox
alt_thick_up_box(0, "AAAAXXJJUUNN", &alt_thick_down_box);

enum {UPPER_LEFT, LOWER_RIGHT};

static void lozenge(int which, int x,int y,int w,int h, gnui::Color color)
{
  w--; h--;
  int d = w <= h ? w : h;
  if (d <= 1) return;
  gnui::setcolor(color);
  if (which == UPPER_LEFT) {
    gnui::strokearc(x+w-d, y, d, d, 45, w<=h ? 180 : 90);
    gnui::strokearc(x, y+h-d, d, d, w<=h ? 180 : 90, 225);
  } else { // LOWER_RIGHT
    gnui::strokearc(x, y+h-d, d, d, 225, w<=h ? 360 : 270);
    gnui::strokearc(x+w-d, y, d, d, w<=h ? 360 : 270, 360+45);
  }
  if (w < h) {
    if (which != UPPER_LEFT) gnui::drawline(x+w, y+d/2, x+w, y+h-d/2);
    if (which != LOWER_RIGHT) gnui::drawline(x, y+d/2, x, y+h-d/2);
  } else if (w > h) {
    if (which != UPPER_LEFT) gnui::drawline(x+d/2, y+h, x+w-d/2, y+h);
    if (which != LOWER_RIGHT) gnui::drawline(x+d/2, y, x+w-d/2, y);
  }
}

static gnui::Style* scrollbarstyle;

// Replace the glyph functions on several widget types:
static void
check_glyph(const gnui::Widget* widget, int t,
		int x, int y, int w, int h, gnui::Flags f)
{
  gnui::Color gbc = widget->color();
  gnui::Color gfc = gnui::inactive(widget->textcolor(), f);
  gnui::Color bc;
  if (f & gnui::SELECTED) bc = widget->selection_color();
  else if (f & gnui::HIGHLIGHT && (bc = widget->highlight_color())) ;
  else bc = widget->buttoncolor();

  if (widget->type() == gnui::Button::RADIO) {

    gnui::Color light = 54, dark = 32;
    if (f&gnui::INACTIVE) {
      light = gnui::inactive(light); dark = gnui::inactive(dark);
    }
    int d = w <= h ? w : h;
//  d = (d - 1)|1;
    d &= (~1);

    gnui::setcolor((f&gnui::VALUE) ? gfc : gbc);
    gnui::fillpie(x+2, y+2, d-4, d-4, 0, 360);

    lozenge(UPPER_LEFT,  x+2, y+1, d-4, d-2, light);
    lozenge(UPPER_LEFT,  x+1, y+2, d-2, d-4, light);
    lozenge(UPPER_LEFT,  x+1, y+1, d-2, d-2, light);
    lozenge(UPPER_LEFT,  x+2, y+2, d-4, d-4, light);

    lozenge(LOWER_RIGHT, x+2, y+1, d-4, d-2, dark);
    lozenge(LOWER_RIGHT, x+1, y+2, d-2, d-4, dark);
    lozenge(LOWER_RIGHT, x+1, y+1, d-2, d-2, dark);
    lozenge(LOWER_RIGHT, x+2, y+2, d-4, d-4, dark);

    lozenge(LOWER_RIGHT, x+1, y,   d-2, d,   light);
    lozenge(LOWER_RIGHT, x,   y+1, d,   d-2, light);
    lozenge(LOWER_RIGHT, x,   y,   d,   d,   light);
    lozenge(LOWER_RIGHT, x+1, y+1, d-2, d-2, light);

    lozenge(UPPER_LEFT,  x+1, y,   d-2, d,   dark);
    lozenge(UPPER_LEFT,  x,   y+1, d,   d-2, dark);
    lozenge(UPPER_LEFT,  x,   y,   d,   d,   dark);
    lozenge(UPPER_LEFT,  x+1, y+1, d-2, d-2, dark);

  } else { // check button:

    w = (w-1)|1; h = (h-1)|1;
    int x1 = x+w/2;
    int y1 = y+h/2;
    gnui::Color light = 54, dark = 32;

    if (f&gnui::INACTIVE) {
      /*bc = gnui::inactive(bc); fc = gnui::inactive(fc);*/
      light = gnui::inactive(light); dark = gnui::inactive(dark);
    }
    gnui::newpath();
    gnui::addvertex(x+3, y1); gnui::addvertex(x1, y+3);
    gnui::addvertex(x+w-4, y1); gnui::addvertex(x1, y+h-4);
    gnui::setcolor((f&gnui::VALUE) ? gfc : gbc);
    gnui::fillpath();

    gnui::setcolor(dark);
    gnui::drawline(x,   y1, x1,  y);  gnui::drawline(x1, y,   x+w-1, y1);
    gnui::drawline(x+1, y1, x1, y+1); gnui::drawline(x1, y+1, x+w-2, y1);
    gnui::setcolor(light);
    gnui::drawline(x+2, y1, x1, y+2); gnui::drawline(x1, y+2, x+w-3, y1);
    gnui::drawline(x+3, y1, x1, y+3); gnui::drawline(x1, y+3, x+w-4, y1);

    gnui::setcolor(light);
    gnui::drawline(x,   y1, x1, y+h-1); gnui::drawline(x1, y+h-1, x+w-1, y1);
    gnui::drawline(x+1, y1, x1, y+h-2); gnui::drawline(x1, y+h-2, x+w-2, y1);
    gnui::setcolor(dark);
    gnui::drawline(x+2, y1, x1, y+h-3); gnui::drawline(x1, y+h-3, x+w-3, y1);
    gnui::drawline(x+3, y1, x1, y+h-4); gnui::drawline(x1, y+h-4, x+w-4, y1);
  }
}

// The main glyph function draws all the arrows:
static void
alt_glyph(const gnui::Widget* widget, int t,
          int x, int y, int w, int h, gnui::Flags f)
{
  gnui::Color bc;
  if (f & gnui::SELECTED) bc = widget->selection_color();
  else if (f & gnui::HIGHLIGHT && (bc = widget->highlight_color())) ;
  else bc = widget->buttoncolor();

  switch (t) {
    case gnui::GLYPH_RIGHT_BUTTON:
    case gnui::GLYPH_LEFT_BUTTON:
    case gnui::GLYPH_UP_BUTTON:
    case gnui::GLYPH_DOWN_BUTTON:
      // erase area behind scrollbars arrows
      gnui::setcolor(widget->color());
      gnui::fillrect(x,y,w,h);
      t -= (gnui::GLYPH_RIGHT_BUTTON-gnui::GLYPH_RIGHT);
      // make it square:
      if (w > h) {x += (w-h)/2; w = h;} else {y += (h-w)/2; h = w;}
      goto JUMP1;
    case gnui::GLYPH_RIGHT:
    case gnui::GLYPH_LEFT:
    case gnui::GLYPH_UP:
    case gnui::GLYPH_DOWN:
    JUMP1:
      {gnui::Color d1, d2, l1, l2;
      if (f&(gnui::VALUE|gnui::SELECTED)) {
        d1 = gnui::GRAY99; d2 = gnui::GRAY85; l1 = gnui::BLACK; l2 = gnui::GRAY60;
      } else{
        l1 = gnui::GRAY99; l2 = gnui::GRAY85; d1 = gnui::BLACK; d2 = gnui::GRAY60;
      }

      if (f&gnui::INACTIVE) {
        l1 = gnui::inactive(l1); l2 = gnui::inactive(l2);
        d1 = gnui::inactive(d1); d2 = gnui::inactive(d2);
      }

      if (t == gnui::GLYPH_RIGHT) {
        gnui::setcolor(bc);
        gnui::newpath();
        gnui::addvertex(x,y); gnui::addvertex(x+w-1, y+h/2); gnui::addvertex(x, y+h-1);
        gnui::fillpath();
        gnui::setcolor(l2); gnui::drawline(x+1,y+h-2, x+1,y+1); gnui::drawline(x+1,y+1, x+w-2,y+h/2);
        gnui::setcolor(d2); gnui::drawline(x+1,y+h-2, x+w-2,y+h/2);
        gnui::setcolor(l1); gnui::drawline(x,y+h-1, x,y); gnui::drawline(x,y, x+w-1,y+h/2);
        gnui::setcolor(d1); gnui::drawline(x,y+h-1, x+w-1,y+h/2);
      } else if (t == gnui::GLYPH_LEFT) {
        gnui::setcolor(bc);
        gnui::newpath();
        gnui::addvertex(x+w-1,y); gnui::addvertex(x+w-1,y+h-1); gnui::addvertex(x,y+h/2);
        gnui::fillpath();
        gnui::setcolor(d2); gnui::drawline(x+w-2,y+1, x+w-2,y+h-2); gnui::drawline(x+w-2,y+h-2, x+1,y+h/2);
        gnui::setcolor(l2); gnui::drawline(x+w-2,y+1, x+1,y+h/2);
        gnui::setcolor(d1); gnui::drawline(x+w-1,y, x+w-1,y+h-1); gnui::drawline(x+w-1,y+h-1, x,y+h/2);
        gnui::setcolor(l1); gnui::drawline(x+w-1,y, x,y+h/2);
      } else if (t == gnui::GLYPH_DOWN) {
        gnui::setcolor(bc);
        gnui::newpath();

        gnui::addvertex(x,y); gnui::addvertex(x+w/2,y+h-1); gnui::addvertex(x+w-1,y);
        gnui::fillpath();
        gnui::setcolor(l2); gnui::drawline(x+w-2,y+1, x+1,y+1); gnui::drawline(x+1,y+1, x+w/2,y+h-2);
        gnui::setcolor(d2); gnui::drawline(x+w-2,y+1, x+w/2,y+h-2);
        gnui::setcolor(l1); gnui::drawline(x+w-1,y, x,y); gnui::drawline(x,y, x+w/2,y+h-1);
        gnui::setcolor(d1); gnui::drawline(x+w-1,y, x+w/2,y+h-1);
      } else { // UP
        gnui::setcolor(bc);
        gnui::newpath();
        gnui::addvertex(x,y+h-1); gnui::addvertex(x+w-1,y+h-1); gnui::addvertex(x+w/2,y);
        gnui::fillpath();
        gnui::setcolor(d2); gnui::drawline(x+1,y+h-2, x+w-2,y+h-2); gnui::drawline(x+w-2,y+h-2, x+w/2,y+1);
        gnui::setcolor(l2); gnui::drawline(x+1,y+h-2, x+w/2,y+1);
        gnui::setcolor(d1); gnui::drawline(x,y+h-1, x+w-1,y+h-1); gnui::drawline(x+w-1,y+h-1, x+w/2,y);
        gnui::setcolor(l1); gnui::drawline(x,y+h-1, x+w/2,y);
      }
      break;
    }
    default:
      widget->buttonbox()->draw(x,y,w,h, bc, f);
  }
}

// Sliders. You need to look at the type of widget to figure out if
// it is horizontal or vertical.
static void
slider_glyph(const gnui::Widget* widget, int t,
          int x, int y, int w, int h, gnui::Flags f)
{
  // draw the up/down arrows using the main glyph function:
  if (t) {
    alt_glyph(widget, t, x, y, w, h, f);
    return;
  }
  gnui::Color bc;
  if (f & gnui::SELECTED) bc = widget->selection_color();
  else if (f & gnui::HIGHLIGHT && (bc = widget->highlight_color())) ;
  else bc = widget->buttoncolor();
  if (widget->type() & 1) { // horizontal
    widget->buttonbox()->draw(x,y,w,h, bc, f);
    widget->buttonbox()->inset(x,y,w,h);
    if (w>10) gnui::THIN_UP_BOX->draw(x+w/2-1, y+1, 2, h-2, bc, f);
    if (w>18) {
      gnui::THIN_UP_BOX->draw(x+w/2-1-4, y+1, 2, h-2, bc, f);
      gnui::THIN_UP_BOX->draw(x+w/2-1+4, y+1, 2, h-2, bc, f);
    }
  } else {
    widget->buttonbox()->draw(x,y,w,h, bc, f);
    widget->buttonbox()->inset(x,y,w,h);
    if (h>10) gnui::THIN_UP_BOX->draw(x+1, y+h/2-1, w-2, 2, bc, f);
    if (h>18) {
      gnui::THIN_UP_BOX->draw(x+1, y+h/2-1-4, w-2, 2, bc, f);
      gnui::THIN_UP_BOX->draw(x+1, y+h/2-1+4, w-2, 2, bc, f);
    }
  }
}

static void choice_glyph(const gnui::Widget* widget, int,
                         int x,int y,int w, int h, gnui::Flags f)
{
  gnui::FLAT_BOX->draw(x,y,w,h,widget->color(),f);
  int H = h/3;
  int Y = y + (h-H)/2;
  widget->buttonbox()->draw(x,Y,w,H,widget->buttoncolor(),f);
}

static void light_glyph(const gnui::Widget* widget, int,
                        int x,int y,int w, int h, gnui::Flags f)
{
  gnui::Color fc = gnui::inactive(widget->textcolor(), f);
  gnui::Color bc = widget->color();
  gnui::DOWN_BOX->draw(x+2, y, w-4, h, bc, f&(~gnui::VALUE));
  gnui::THIN_UP_BOX->draw(x+4, y+2, w-8, h-4, f&gnui::VALUE ? fc : bc, f&(~gnui::VALUE));
}

static void return_glyph(const gnui::Widget*, int,
                         int x,int y,int w,int h, gnui::Flags f)
{
  int size = w; if (h<size) size = h;
  int d = (size+2)/4; if (d<3) d = 3;
  int t = (size+9)/12; if (t<1) t = 1;
  int x0 = x+(w-2*d-2*t-1)/2;
  int x1 = x0+d;
  int y0 = y+h/2;
  gnui::setcolor(gnui::inactive(gnui::GRAY33, f));
  gnui::drawline(x0, y0, x1, y0+d);
  gnui::drawline(x1, y0+d, x1, y0+t);
  gnui::drawline(x1, y0+t, x1+d+2*t, y0+t);
  gnui::drawline(x1+d+2*t, y0+t, x1+d+2*t, y0-d);
  gnui::drawline(x1, y0-t, x1, y0-d);
  gnui::setcolor(gnui::inactive(gnui::GRAY90, f));
  gnui::drawline(x0, y0, x1, y0-d);
  gnui::drawline(x1+1, y0-t, x1+d, y0-t);
  gnui::drawline(x1+d, y0-t, x1+d, y0-d);
  gnui::drawline(x1+d, y0-d, x1+d+2*t, y0-d);
}

extern "C" bool fltk_theme() {
  //gnui::Style::draw_sliders_pushed = 1;

  gnui::Widget::default_style->glyph = alt_glyph;

  gnui::Style* s;

  if ((s = gnui::Style::find("menu bar"))) {
    s->buttonbox = gnui::HIGHLIGHT_UP_BOX;
  }

  if ((s = gnui::Style::find("item"))) {
    s->glyph = check_glyph;
    s->buttonbox = gnui::NO_BOX;
  }

  if ((s = gnui::Style::find("menu button"))) {
    s->glyph = alt_glyph;
  }

  if ((s = gnui::Style::find("choice"))) {
    s->box = gnui::UP_BOX;
    s->glyph = choice_glyph;
  }

  if ((s = gnui::Style::find("check button"))) {
    s->glyph = check_glyph;
  }

  if ((s = gnui::Style::find("return button"))) {
    s->glyph = return_glyph;
  }

  if ((s = gnui::Style::find("light button"))) {
    s->glyph = light_glyph;
  }

  if ((s = gnui::Style::find("scrollbar"))) {
    scrollbarstyle = s;
    s->glyph = slider_glyph;
  }

  if ((s = gnui::Style::find("slider"))) {
    s->glyph = slider_glyph;
  }

  if ((s = gnui::Style::find("value slider"))) {
    s->glyph = slider_glyph;
  }

  if ((s = gnui::Style::find("input browser"))) {
    s->glyph = alt_glyph;
  }

  return true;
}

//
// End of "$Id$".
//
