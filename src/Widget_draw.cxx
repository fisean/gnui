//
// "$Id$"
//
// Copyright 1998-2003 by Bill Spitzak and others.
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
// Please report all bugs and problems to "fltk-bugs@fltk.org".

// Originally this contained the definition of LabelType. It now
// contains all the drawing code used by widgets.

#include <fltk/LabelType.h>
#include <fltk/Box.h>
#include <fltk/Image.h>
#include <fltk/Widget.h>
#include <fltk/Window.h>
#include <fltk/damage.h>
#include <fltk/draw.h>
#include <fltk/string.h>
#include <config.h>
using namespace fltk;

LabelType* LabelType::find(const char* name) {
  for (LabelType* p = LabelType::first; p; p = p->next)
    if (p->name && !strcasecmp(name, p->name)) return p;
  return 0;
}

LabelType* LabelType::first = 0;

////////////////////////////////////////////////////////////////

void LabelType::draw(const char* label,
		     const Rectangle& r,
		     Flags flags) const
{
  if (drawflags(INACTIVE)) {
    Color fg = getcolor();
    setcolor(GRAY90);
    Rectangle r1(r); r1.move(1,1);
    drawtext(label, r1, flags);
    setcolor(fg);
  }
  drawtext(label, r, flags);
}

static LabelType normalLabel("normal");
LabelType* const fltk::NORMAL_LABEL = &normalLabel;
LabelType* const fltk::SYMBOL_LABEL = &normalLabel;

////////////////////////////////////////////////////////////////

class FL_API NoLabel : public LabelType {
public:
  void draw(const char*, const Rectangle&, Flags) const {}
  NoLabel(const char * n) : LabelType(n) {}
};
static NoLabel noLabel("none");
LabelType* const fltk::NO_LABEL = &noLabel;

////////////////////////////////////////////////////////////////
// Drawing methods (designed to be called from a draw() implementation):

/** Draw the widget's box() such that it fills the entire area of the
    widget. If the box is not rectangluar, this also draws the area
    of the parent widget that is exposed.

    This also does drawstyle(style(),flags()&~OUTPUT) and thus the
    colors and font are set up for drawing text in the widget.
*/
void Widget::draw_box() const {
#if USE_CLIPOUT
  if (damage()&DAMAGE_EXPOSE && !box()->fills_rectangle() && parent())
    draw_background();
#endif
  drawstyle(style(), flags_ & ~OUTPUT);
  box()->draw(Rectangle(w(),h()));
  // draw a big x to show where image will be drawn:
//    setcolor(BLACK);
//    drawline(0,0,w(),h());
//    drawline(0,h(),w(),0);
}

/** Same as draw_box() but draws only the boundary of the box() by
    calling it's draw routine with the INVISIBLE flag set. This only
    works for rectangular boxes.  This is useful for avoiding blinking
    during update for widgets that erase their contents as part of
    redrawing them anyway (ie anything displaying text).
*/
void Widget::draw_frame() const {
  drawstyle(style(), flags_ & ~OUTPUT | INVISIBLE);
  box()->draw(Rectangle(w(),h()));
  setdrawflags(flags_);
}

/** Calls draw_label() with the area inside the box() and with the
    alignment stored in flags(). The labelfont() and labelcolor()
    are used. For historic reasons if the OUTPUT flag is on then
    the textfont() and textcolor() are used.
*/
void Widget::draw_label() const {
  Flags flags = this->flags();
  // Do a quick test to see if we don't want to draw anything:
  if (!image() && (!label() || !*label() ||
		   (flags&15) && !(flags & ALIGN_INSIDE))) return;
  // figure out the inside of the box():
  Rectangle r(w(),h()); box()->inset(r);
  // and draw it:
  drawstyle(style(), this->flags() ^ OUTPUT);
  draw_label(r, flags);
}

/** Draws labels inside the widget using the current font and color
    settings. \a XYWH is the bounding box to
    fit the label into, \a flags is used to align in that box.

    If the flags contain any ALIGN flags and don't have ALIGN_INSIDE
    then the label() is not drawn. Instead the image() is drawn to
    fill the box (most image() types will center the picture).

    Otherwise it tries to put both the label() and the image() into the
    box in a nice way. The image() is put against the side that any
    ALIGN flags say, and then the label() is put next to that.
*/
void Widget::draw_label(const Rectangle& ir, Flags flags) const
{
  // If label is drawn outside, draw the image only:
  if ((flags&15) && !(flags & ALIGN_INSIDE)) {
    if (!image_) return;
    int fw = ir.w();
    int fh = ir.h();
    image_->measure(fw, fh);
    if (flags & ALIGN_CLIP) push_clip(ir);
    Rectangle cr(ir,fw,fh);
    image_->draw(cr);
    if (flags & ALIGN_CLIP) pop_clip();
    return;
  }

  Rectangle r(ir);
  if (image_) {

    int w = r.w();
    int h = r.h();
    image_->measure(w, h);

    // If all flags including ALIGN_INSIDE are off it changes how
    // label and image are printed so they are both centered "nicely"
    // in the button:
    if (label_ && !(flags&0x1f) && !(label_[0]=='@' && label_[1]==';')) {
      int d = (r.h()-int(h+labelsize()+leading()+.5))>>1;
      if (d >= 0) {
	// put the image atop the text
	r.move_y(d); flags |= ALIGN_TOP;
      } else if (w < r.w()) {
	int text_w = r.w(); int text_h = r.h();
	measure(label_, text_w, text_h, flags);
	int d = (r.w()-(w+text_w))>>1;
	if (d > 0) {
	  r.move_x(d);
	  flags |= ALIGN_LEFT;
	}
      }
    }

    if (flags & ALIGN_CLIP) push_clip(r);

    Rectangle ir(r, w, h, flags);
    image_->draw(ir);

    // figure out the rectangle that remains for text:
    if (flags & ALIGN_TOP) r.set_y(ir.b());
    else if (flags & ALIGN_BOTTOM) r.set_b(ir.y());
    else if (flags & ALIGN_LEFT) r.set_x(ir.r());
    else if (flags & ALIGN_RIGHT) r.set_r(ir.x());
    else {r.set_y(ir.b()); /*flags |= ALIGN_TOP;*/}
  }

  if (r.w()>0 && label_ && *label_) {
    // add some interior border for the text:
    if (r.w() > 6 && flags&ALIGN_LEFT) {
      if (r.w() > 9) {r.move_x(3); r.move_r(-3);}
      else r.set_x(r.r()-6);
    }
    if (r.w() > 6 && flags&ALIGN_RIGHT) {
      if (r.w() > 9) r.move_r(-6);
      else r.w(6);
    }
    if (!image_ && (flags & ALIGN_CLIP)) push_clip(r);
    labeltype()->draw(label_, r, flags);
  } else {
    if (!image_) return; // don't call pop_clip if push_clip was not called
  }

  if (flags & ALIGN_CLIP) pop_clip();
}

/**
  Groups normally call this to draw the label() outside a widget.
  This uses the flags() to determine where to put the label. If
  the ALIGN flags are all zero, or if ALIGN_INSIDE is turned
  on, then nothing is done. Otherwise the align is used to select
  a rectangle outside the widget and the widget's label() is
  formatted into that area.

  The font is set to labelfont()/labelsize(), and labelcolor()
  is used to color the text. The flags are passed to the draw()
  function, but with the alignment changed to put the text against
  the widget, and INACTIVE is added if active_r() is false.

  The image() of the widget is not drawn by this. It is always
  drawn inside the widget.
*/
void Group::draw_outside_label(Widget& w) const {
  Flags flags = w.flags();
  if (flags & INVISIBLE) return;
  // skip any labels that are inside the widget:
  if (!(flags&15) || (flags & ALIGN_INSIDE)) return;
  if (!w.label() || !*w.label()) return;
  // invent a box that is outside the widget:
  Rectangle r(w);
  if (flags & ALIGN_TOP) {
    if (flags & ALIGN_BOTTOM) {
      // special cases to align on left or right side at top/bottom
      if (flags & ALIGN_LEFT) {
	flags &= ~(ALIGN_TOP|ALIGN_LEFT);
      } else {
	flags &= ~ALIGN_BOTTOM;
      }
      if (flags & ALIGN_RIGHT) {
	r.x(r.r()+3);
	r.set_r(this->w());
	flags = flags&~ALIGN_RIGHT | ALIGN_LEFT;
      } else {
	r.x(0);
	r.w(w.x()-3);
	flags = flags | ALIGN_RIGHT;
      }
    } else {
      flags ^= (ALIGN_BOTTOM|ALIGN_TOP);
      r.y(0);
      r.h(w.y());
    }
  } else if (flags & ALIGN_BOTTOM) {
    flags ^= (ALIGN_BOTTOM|ALIGN_TOP);
    r.y(r.b());
    r.set_b(h());
  } else if (flags & ALIGN_LEFT) {
    flags ^= (ALIGN_LEFT|ALIGN_RIGHT);
    r.x(0);
    r.w(w.x()-3);
  } else if (flags & ALIGN_RIGHT) {
    flags ^= (ALIGN_LEFT|ALIGN_RIGHT);
    r.x(r.r()+3);
    r.set_r(this->w());
  }
  flags = flags & ~(HIGHLIGHT|SELECTED|PUSHED) | OUTPUT;
  drawstyle(w.style(), flags);
  //push_clip(X, Y, W, H); // this will break some old fltk programs
  w.labeltype()->draw(w.label(), r, flags);
  //pop_clip();
}

/** Replace \a w and \a h with the size of the area the label will
    take up. This is the size of the draw_outside_label() and thus
    does not include any image() and always uses the labelfont even
    if the OUTPUT flag is set.

    If the ALIGN_WRAP flag is set this chooses the rather arbitrary
    width of 300 to wrap the label at. Ideally this should have been
    passed in \a w but is not for back-compatability reasons.
*/
void Widget::measure_label(int& w, int& h) const {
  setfont(labelfont(), labelsize());
  w = h = 300; // rather arbitrary choice for maximum wrap width
  measure(label(), w, h, flags());
}

//
// End of "$Id$".
//