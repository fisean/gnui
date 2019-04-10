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

// fltk classic appearance

#include <fltk/Widget.h>
#include <fltk/CheckButton.h>
#include <fltk/Scrollbar.h>
#include <fltk/Input.h>
#include <fltk/Output.h>
#include <fltk/Style.h>
#include <fltk/Box.h>
#include <string.h>

static void choice_glyph(const gnui::Widget* widget, int,
			 int x,int y,int w,int h, gnui::Flags f)
{
  int H = 7;
  gnui::THIN_UP_BOX->draw(x, y+(h-H)/2, w-4, H, widget->buttoncolor(), f);
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
static const Motif_Labeltype motif_label(0);

static gnui::FrameBox always_up_box(0, "AAAAWUJJUTNN");
static gnui::HighlightBox menu_title_box(0, &always_up_box);

static gnui::FrameBox classic_down_box(0, "NNTUJJUWAAAA");
static gnui::FrameBox classic_up_box(0, "AAAAWUJJUTNN", &classic_down_box);

extern "C" bool fltk_theme() {

  gnui::get_system_colors();

  gnui::Widget::default_style->buttonbox = &classic_up_box;
  gnui::Widget::default_style->box = &classic_down_box;
  gnui::Widget::default_style->highlight_color = 0;
  gnui::Widget::default_style->labelsize = 14;
  gnui::Widget::default_style->textsize = 14;
  gnui::Widget::default_style->selection_color = gnui::GRAY60;
  gnui::Widget::default_style->selection_textcolor = 0;

  gnui::Style* s;
  if ((s = gnui::Style::find("button"))) {
    s->box = &classic_up_box;
  }
  if ((s = gnui::Style::find("menu"))) {
    s->selection_color = gnui::WHITE;
    s->selection_textcolor = 0;
    s->color = gnui::GRAY75;
  }
  if ((s = gnui::Style::find("item"))) {
    s->textcolor = gnui::BLACK;
  }
  if ((s = gnui::Style::find("menu_bar"))) {
    s->buttonbox = &menu_title_box;
    s->selection_color = gnui::GRAY75;
  }
  if ((s = gnui::Style::find("check_button"))) {
    s->textcolor = gnui::BLACK;
    //s->buttoncolor = gnui::GRAY;
  }
  if ((s = gnui::Style::find("output"))) {
    s->color = gnui::GRAY75;
  }
  if ((s = gnui::Style::find("choice"))) {
    s->glyph = choice_glyph;
  }
  return true;
}

//
// End of "$Id$".
//
