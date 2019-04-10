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

// Motif L&F theme plugin for fltk.  A good example of the capabilities
// of theme plugins.

#include <fltk/Widget.h>
#include <fltk/CheckButton.h>
#include <fltk/Scrollbar.h>
#include <fltk/Input.h>
#include <fltk/Output.h>
#include <fltk/Style.h>
#include <fltk/Box.h>
#include <fltk/draw.h>

// some new boxtypes (look familiar?)
static gnui::FrameBox
thick_motif_down_box("motif thick down", "HHVVHHVVHHVV");

static gnui::FrameBox
thick_motif_up_box("motif thick up", "VVHHVVHHVVHH", &thick_motif_down_box);

static gnui::HighlightBox
thick_motif_highlight_box("motif thick highlight", &thick_motif_up_box);

static gnui::HighlightBox
thick_motif_menu_box("motif thick menu", &thick_motif_up_box);

static gnui::FrameBox
thin_motif_down_box("motif down", "HHVVHHVV");

static gnui::FrameBox
thin_motif_up_box("motif up","VVHHVVHH",&thin_motif_down_box);

static gnui::HighlightBox
thin_motif_highlight_box("motif thin highlight", &thin_motif_up_box);

static gnui::FrameBox
thin_motif_always_up_box("motif up","VVHHVVHH");

static gnui::HighlightBox
thin_motif_menu_box("motif thin menu", &thin_motif_always_up_box);

static void motif_check_glyph(const gnui::Widget* widget, int t,
			int x, int y, int w, int h, gnui::Flags f)
{
  gnui::Color fc = gnui::inactive(widget->textcolor(), f);
  gnui::Color bc = widget->color();
  if (widget->type()==gnui::Button::RADIO) {
    w = (w-1)|1; h = (h-1)|1;
    int x1 = x+w/2;
    int y1 = y+h/2;
    gnui::Color light = gnui::GRAY90, dark = gnui::GRAY33;
    if (f&gnui::VALUE) { light = gnui::GRAY33; dark = gnui::GRAY90; }
//  if (f&gnui::INACTIVE)
//    { light = gnui::inactive(light); dark = gnui::inactive(dark); }
    gnui::setcolor((f & gnui::VALUE) ? fc : bc);
    gnui::addvertex(x+3,y1); gnui::addvertex(x1+1,y+2); gnui::addvertex(x+w-3,y1); gnui::addvertex(x1,y+h-4);
    gnui::fillpath();

    gnui::setcolor(light); gnui::drawline(x, y1, x1, y); gnui::drawline(x1, y, x+w-1, y1);
    gnui::setcolor(light); gnui::drawline(x+1, y1, x1, y+1); gnui::drawline(x1, y+1, x+w-2, y1);
    gnui::setcolor(light); gnui::drawline(x+2, y1, x1, y+2); gnui::drawline(x1, y+2, x+w-3, y1);

    gnui::setcolor(dark); gnui::drawline(x, y1, x1, y+h-1); gnui::drawline(x1, y+h-1, x+w-1, y1);
    gnui::setcolor(dark); gnui::drawline(x+1, y1, x1, y+h-2); gnui::drawline(x1, y+h-2, x+w-2, y1);
    gnui::setcolor(dark); gnui::drawline(x+2, y1, x1, y+h-3); gnui::drawline(x1, y+h-3, x+w-3, y1);
  } else {
    x += 2; y += 2; w -= 4; h -= 4; // fudge factor
    thin_motif_up_box.draw(x, y, w, h,
			   (f & gnui::VALUE) ? fc : bc, f);
  }
}

static void motif_glyph(const gnui::Widget* widget, int t,
			int x, int y, int w, int h, gnui::Flags f)
{
  gnui::Color bc = widget->buttoncolor();
  switch (t) {
    case gnui::GLYPH_RIGHT_BUTTON:
    case gnui::GLYPH_LEFT_BUTTON:
    case gnui::GLYPH_UP_BUTTON:
    case gnui::GLYPH_DOWN_BUTTON:
      // draw background of scroll buttons
      gnui::setcolor(widget->color());
      gnui::fillrect(x,y,w,h);
      goto JUMP1;
    case gnui::GLYPH_RIGHT:
    case gnui::GLYPH_LEFT:
    case gnui::GLYPH_UP:
    case gnui::GLYPH_DOWN:
      // menu fudge factor
      if (w > 10) {x += (w-10)/2; y += (w-10)/2; w = h = 10;}
//	x += 2; y += 2; w -= 4; h -= 4;
//	x += 4; y += 4; w -= 8; h -= 8;
    JUMP1:
      if (h > w) {y += (h-w)/2; h = w;}
      else if (w > h) {x += (w-h)/2; w = h;}
      {gnui::Color d1, d2, l1, l2;
      if (f&gnui::VALUE) {
        d1 = gnui::GRAY90; d2 = gnui::GRAY90; l1 = gnui::GRAY33; l2 = gnui::GRAY33;
      } else{
        l1 = gnui::GRAY90; l2 = gnui::GRAY90; d1 = gnui::GRAY33; d2 = gnui::GRAY33;
      }

//       if (f&gnui::INACTIVE) {
//         l1 = gnui::inactive(l1); l2 = gnui::inactive(l2);
//         d1 = gnui::inactive(d1); d2 = gnui::inactive(d2);
//       }

      switch (t) {
      case gnui::GLYPH_RIGHT:
      case gnui::GLYPH_RIGHT_BUTTON:
        gnui::setcolor(bc); gnui::newpath(); gnui::addvertex(x, y); gnui::addvertex(x+w-1, y+h/2);
        gnui::addvertex(x,y+h-1); gnui::closepath(); gnui::fillpath();
        gnui::setcolor(l2); gnui::drawline(x+2,y+2, x+w-3,y+h/2);
        gnui::setcolor(d2); gnui::drawline(x+2,y+h-3, x+w-3,y+h/2);
        gnui::setcolor(l2); gnui::drawline(x+1,y+h-2, x+1,y+1); gnui::drawline(x+1,y+1, x+w-2,y+h/2);
        gnui::setcolor(d2); gnui::drawline(x+1,y+h-2, x+w-2,y+h/2);
        gnui::setcolor(l1); gnui::drawline(x,y+h-1, x,y); gnui::drawline(x,y, x+w-1,y+h/2);
        gnui::setcolor(d1); gnui::drawline(x,y+h-1, x+w-1,y+h/2);
        break;
      case gnui::GLYPH_LEFT:
      case gnui::GLYPH_LEFT_BUTTON:
        gnui::setcolor(bc); gnui::newpath(); gnui::addvertex(x+w-1, y); gnui::addvertex(x+w-1, y+h-1);
        gnui::addvertex(x,y+h/2); gnui::closepath(); gnui::fillpath();
        gnui::setcolor(d2); gnui::drawline(x+w-3,y+h-3, x+2,y+h/2);
        gnui::setcolor(l2); gnui::drawline(x+w-3,y+2, x+2,y+h/2);
        gnui::setcolor(d2); gnui::drawline(x+w-2,y+1, x+w-2,y+h-2); gnui::drawline(x+w-2,y+h-2, x+1,y+h/2);
        gnui::setcolor(l2); gnui::drawline(x+w-2,y+1, x+1,y+h/2);
        gnui::setcolor(d1); gnui::drawline(x+w-1,y, x+w-1,y+h-1); gnui::drawline(x+w-1,y+h-1, x,y+h/2);
        gnui::setcolor(l1); gnui::drawline(x+w-1,y, x,y+h/2);
        break;
      case gnui::GLYPH_DOWN:
      case gnui::GLYPH_DOWN_BUTTON:
        gnui::setcolor(bc); gnui::newpath(); gnui::addvertex(x, y); gnui::addvertex(x+w/2, y+h-1);
        gnui::addvertex(x+w-1,y); gnui::closepath(); gnui::fillpath();
        gnui::setcolor(l2); gnui::drawline(x+2,y+2, x+w/2,y+h-3);
        gnui::setcolor(d2); gnui::drawline(x+w-3,y+2, x+w/2,y+h-3);
        gnui::setcolor(l2); gnui::drawline(x+w-2,y+1, x+1,y+1); gnui::drawline(x+1,y+1, x+w/2,y+h-2);
        gnui::setcolor(d2); gnui::drawline(x+w-2,y+1, x+w/2,y+h-2);
        gnui::setcolor(l1); gnui::drawline(x+w-1,y, x,y); gnui::drawline(x,y, x+w/2,y+h-1);
        gnui::setcolor(d1); gnui::drawline(x+w-1,y, x+w/2,y+h-1);
        break;
      case gnui::GLYPH_UP:
      case gnui::GLYPH_UP_BUTTON:
        gnui::setcolor(bc); gnui::newpath(); gnui::addvertex(x, y+h-1); gnui::addvertex(x+w-1, y+h-1);
        gnui::addvertex(x+w/2,y); gnui::closepath(); gnui::fillpath();
        gnui::setcolor(d2); gnui::drawline(x+w-3,y+h-3, x+w/2,y+2);
        gnui::setcolor(l2); gnui::drawline(x+2,y+h-3, x+w/2,y+2);
        gnui::setcolor(d2); gnui::drawline(x+1,y+h-2, x+w-2,y+h-2); gnui::drawline(x+w-2,y+h-2, x+w/2,y+1);
        gnui::setcolor(l2); gnui::drawline(x+1,y+h-2, x+w/2,y+1);
        gnui::setcolor(d1); gnui::drawline(x,y+h-1, x+w-1,y+h-1); gnui::drawline(x+w-1,y+h-1, x+w/2,y);
        gnui::setcolor(l1); gnui::drawline(x,y+h-1, x+w/2,y);
        break;
      }
      break;
    }
    default:
      gnui::Widget::default_glyph(widget, t, x,y,w,h, f);
  }
}

static void choice_glyph(const gnui::Widget* widget, int,
			 int x,int y,int w,int h, gnui::Flags f)
{
  gnui::Color color = widget->color();
  gnui::setcolor(color);
  gnui::fillrect(x,y,w,h);
  int H = h/3;
  y += (h-H)/2;
  h = H;
  widget->box()->draw(x,y,w,h,color,f);
}

#include <fltk/LabelType.h>
// Disable the engraving of inactive labels:
class Motif_Labeltype : public gnui::LabelType {
public:
  void draw(const char* label,
	    int X, int Y, int W, int H,
	    gnui::Color c, gnui::Flags f) const
    {
      if (f & gnui::INACTIVE) {
	c = gnui::inactive(c);
	f &= ~gnui::INACTIVE;
      }
      gnui::NORMAL_LABEL->draw(label, X,Y,W,H,c,f);
    }
  Motif_Labeltype(const char*n) : gnui::LabelType(n) {}
};
static Motif_Labeltype motif_label(0);

// This is the function that is called by fltk when the plugin is loaded:
extern "C" bool fltk_theme()
{
  // On X gnui::get_system_colors reads the XResource database for
  // some Motif-like things like *background:
  gnui::get_system_colors();

  gnui::Style::draw_boxes_inactive = false;

  gnui::Widget::default_style->buttonbox = &thin_motif_up_box;
  gnui::Widget::default_style->focusbox = &thin_motif_down_box;
  gnui::Widget::default_style->box = &thin_motif_down_box;
  gnui::Widget::default_style->color = gnui::GRAY75;
  gnui::Widget::default_style->selection_color = gnui::BLACK;
  gnui::Widget::default_style->selection_textcolor = gnui::GRAY75;
  gnui::Widget::default_style->glyph = motif_glyph;
  gnui::Widget::default_style->labeltype = &motif_label;

  gnui::Style* s;

  if ((s = gnui::Style::find("button"))) {
    s->box = &thin_motif_up_box;
  }

  if ((s = gnui::Style::find("menu"))) {
    s->buttonbox = &thin_motif_menu_box; // this does not work anymore...
    //s->leading = 0;
  }

  if ((s = gnui::Style::find("menu bar"))) {
    s->buttonbox = &thin_motif_menu_box;
  }

  if ((s = gnui::Style::find("menu button"))) {
    s->buttonbox = &thin_motif_menu_box;
  }

  if ((s = gnui::Style::find("choice"))) {
    s->box = &thin_motif_up_box;
    s->glyph = choice_glyph;
  }

  if ((s = gnui::Style::find("scrollbar"))) {
    s->box = &thin_motif_down_box;
    s->color = gnui::GRAY66;
  }

  if ((s = gnui::Style::find("slider"))) {
    s->box = &thin_motif_down_box;
    s->color = gnui::GRAY66;
  }

  if ((s = gnui::Style::find("value slider"))) {
    s->color = gnui::GRAY66;
  }

  if ((s = gnui::Style::find("highlight button"))) {
    s->box = &thin_motif_highlight_box;
    s->highlight_color = gnui::GRAY75;
  }

  if ((s = gnui::Style::find("check button"))) {
    s->buttoncolor = gnui::GRAY66;
    s->glyph = motif_check_glyph;
  }

  if ((s = gnui::Style::find("radio button"))) {
    s->buttoncolor = gnui::GRAY66;
  }

  return true;
}

//
// End of "$Id$"
//
