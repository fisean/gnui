//
// "$Id: Fl_Style.cxx,v 1.12 2000/04/11 08:16:44 bill Exp $"
//
// Code for managing Fl_Style structures.
//
// Copyright 1998-1999 by Bill Spitzak and others.
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
// Please report all bugs and problems to "fltk-bugs@easysw.com".
//

#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <string.h>

Fl_Named_Style* Fl_Named_Style::first;

// Do not change the contents of this ever.  The themes depend on getting
// a known state initially.
static void revert(Fl_Style* s) {
  s->box                   = FL_NORMAL_BOX;
  s->window_box            = FL_DOWN_BOX;
  s->glyph                 = fl_glyph;
  s->label_font            = FL_HELVETICA;
  s->text_font             = FL_HELVETICA;
  s->label_type            = FL_NORMAL_LABEL;
  s->color                 = FL_GRAY;
  s->label_color           = FL_BLACK;
  s->selection_color	   = FL_BLUE_SELECTION_COLOR;
  s->selection_text_color  = FL_WHITE;
  s->window_color          = FL_LIGHT2;
  s->highlight_color       = FL_NO_COLOR;
  s->highlight_label_color = FL_NO_COLOR;
  s->text_color            = FL_BLACK;
  s->label_size		   = 12;
  s->text_size             = 12;
  s->leading		   = 2;
  s->parent                = 0;	// this is the topmost style always
}

Fl_Named_Style* Fl_Widget::default_style;

// Copying a style pointer from another widget is not safe if that
// style is dynamic() because it may change or be deleted.  This makes
// another dynamic() copy if necessary.

int Fl_Widget::copy_style(const Fl_Style* t) {
  if (style_ == t) return 0;
  if (style_ && style_->dynamic()) delete (Fl_Style*)style_;
  if (!t->dynamic()) {style_ = t; return 0;}
  Fl_Style* newstyle = new Fl_Style;
  newstyle->parent = (Fl_Style*)t;
  style_ = newstyle;
  return 1;
}

// Widgets set their own attributes by (possibly) creating a unique copy
// of their current style and setting it there.  Because this copy does
// not have any children the recursive search is not needed:

Fl_Style* fl_unique_style(const Fl_Style* & pointer) {
  if (pointer->dynamic()) return (Fl_Style*)pointer;
  Fl_Style* newstyle = new Fl_Style;
  newstyle->parent = (Fl_Style*)pointer;
  pointer = newstyle;
  return newstyle;
}

// Retrieve/set values from a style, using parent's value if not in child:

#define style_functions(TYPE,FIELD)	\
TYPE Fl_Widget::FIELD() const {		\
  for (const Fl_Style* s = style_;;) {	\
    if (s->FIELD) return s->FIELD;	\
    s = s->parent;			\
    if (!s) return 0;			\
  }					\
}					\
void Fl_Widget::FIELD(TYPE v) {		\
  fl_unique_style(style_)->FIELD = v;	\
}

style_functions(Fl_Boxtype,box);
style_functions(Fl_Boxtype,window_box);
style_functions(Fl_Glyph,glyph);
style_functions(Fl_Font,label_font);
style_functions(Fl_Font,text_font);
style_functions(Fl_Labeltype,label_type);
style_functions(Fl_Color,color);
style_functions(Fl_Color,label_color);
style_functions(Fl_Color,selection_color);
style_functions(Fl_Color,selection_text_color);
style_functions(Fl_Color,window_color);
style_functions(Fl_Color,highlight_color);
style_functions(Fl_Color,highlight_label_color);
style_functions(Fl_Color,text_color);
style_functions(unsigned,label_size);
style_functions(unsigned,text_size);
style_functions(unsigned,leading);

// Named styles provide a list that can be searched by theme plugins.
// The "revert" function is mostly provided to make it easy to initialize
// the fields even though C++ does not allow a structure constant.
// It is also used to undo theme changes.

static void plainrevert(Fl_Style*) {}

Fl_Named_Style::Fl_Named_Style(const char* n, void (*revert)(Fl_Style*), Fl_Named_Style** pds) {
  static bool init = 0;
  memset((void*)this, 0, sizeof(*this));
  if (!init) {
    init = 1;
    Fl_Widget::default_style = new Fl_Named_Style("default", ::revert, &Fl_Widget::default_style);
  }
  parent = Fl_Widget::default_style; // revert may want to change this
  if (revert) { revertfunc = revert; revert(this); }
  else revertfunc = plainrevert;
  next = Fl_Named_Style::first;
  Fl_Named_Style::first = this;
  back_pointer = pds;
  name = n;
}

// This constructor is used to create dynamic() styles for widgets that
// change their own attributes:
Fl_Style::Fl_Style() {
  memset((void*)this, 0, sizeof(*this));
}

int Fl_Style::draw_boxes_inactive = 1;

#include <ctype.h>
Fl_Named_Style* Fl_Style::find(const char* name) {
  for (Fl_Named_Style* p = Fl_Named_Style::first; p; p = p->next) {
    const char* a = p->name;
    const char* b = name;
    if (!a) continue;
    for (;;) {
      if (*a == '_') {
	if (*b == ' ' || *b == '_');
	else {a++; continue;}
      } else if (tolower(*a) != tolower(*b)) break;
      if (!*a && !*b) return p;
      a++;
      b++;
    }
  }
  return 0;
}

//
// End of "$Id: Fl_Style.cxx,v 1.12 2000/04/11 08:16:44 bill Exp $".
//
