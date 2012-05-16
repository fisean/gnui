//
// "$Id$"
//
// Window type code for the Fast Light Tool Kit (FLTK).
//
// The widget describing an fltk3::Window.  This is also all the code
// for interacting with the overlay, which allows the user to
// select, move, and resize the children widgets.
//
// Copyright 1998-2010 by Bill Spitzak and others.
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
//     http://www.fltk.org/str.php
//

#include <fltk3/run.h>
#include <fltk3/OverlayWindow.h>
#include <fltk3/message.h>
#include <fltk3/draw.h>
#include <fltk3/x.h>
#include <fltk3/MenuItem.h>
#include <fltk3/RoundButton.h>
#include <fltk3/Wrapper.h>
#include "Fl_Widget_Type.h"
#include "undo.h"
#include <math.h>
#include <stdlib.h>
#include "alignment_panel.h"
#include <stdio.h>

extern int gridx;
extern int gridy;
extern int snap;
extern int show_guides;

int include_H_from_C = 1;
int use_FL_COMMAND = 0;
extern int i18n_type;
extern const char* i18n_include;
extern const char* i18n_function;
extern const char* i18n_file;
extern const char* i18n_set;

extern fltk3::Preferences	fluid_prefs;

inline int fl_min(int a, int b) { return (a < b ? a : b); } 

#include "widget_panel.h"

// Update the XYWH values in the widget panel...
static void update_xywh() {
  if (Fl_Panel::current && Fl_Panel::current->is_widget()) {
    widget_x_input->value(((Fl_Widget_Type *)Fl_Panel::current_widget())->o->x());
    widget_y_input->value(((Fl_Widget_Type *)Fl_Panel::current_widget())->o->y());
    widget_w_input->value(((Fl_Widget_Type *)Fl_Panel::current_widget())->o->w());
    widget_h_input->value(((Fl_Widget_Type *)Fl_Panel::current_widget())->o->h());
  }
}

void guides_cb(fltk3::CheckButton *i, long) {
  show_guides = i->value();
  fluid_prefs.set("show_guides", show_guides);

  for (Fl_Type *p = Fl_Type::first; p; p = p->next) {
    if (p->is_window()) {
      Fl_Window_Type *w = (Fl_Window_Type *)p;
      ((fltk3::OverlayWindow *)(w->o))->redraw_overlay();
    }
  }
}

void grid_cb(fltk3::IntInput *i, long v) {
  int n = atoi(i->value());
  if (n < 0) n = 0;
  switch (v) {
    case 1:
      gridx = n;
      fluid_prefs.set("gridx", n);
      break;
    case 2:
      gridy = n;
      fluid_prefs.set("gridy", n);
      break;
    case 3:
      snap = n;
      fluid_prefs.set("snap", n);
      break;
  }

  // Next go through all of the windows in the project and set the
  // stepping for resizes...
  Fl_Type *p;
  Fl_Window_Type *w;

  for (p = Fl_Type::first; p; p = p->next) {
    if (p->is_window()) {
      w = (Fl_Window_Type *)p;
      ((fltk3::Window *)(w->o))->size_range(gridx, gridy,
                                        fltk3::w(), fltk3::h(),
                                        gridx, gridy, 0);
    }
  }
}

// Set default widget sizes...
void default_widget_size_cb(fltk3::RoundButton *b, long size) {
  // Update the "normal" text size of new widgets...
  b->setonly();
  Fl_Widget_Type::default_size = size;
  fluid_prefs.set("widget_size", Fl_Widget_Type::default_size);
}


void proj_version_cb(fltk3::Choice*, void*) {
  // TODO: change version number of .fl file and fix database
  set_modflag(1);
}


void i18n_type_cb(fltk3::Choice *c, void *) {
  undo_checkpoint();

  switch (i18n_type = c->value()) {
  case 0 : /* None */
      i18n_include_input->hide();
      i18n_file_input->hide();
      i18n_set_input->hide();
      i18n_function_input->hide();
      break;
  case 1 : /* GNU gettext */
      i18n_include_input->value("<libintl.h>");
      i18n_include = i18n_include_input->value();
      i18n_function_input->value("gettext");
      i18n_function = i18n_function_input->value();
      i18n_include_input->show();
      i18n_file_input->hide();
      i18n_set_input->hide();
      i18n_function_input->show();
      break;
  case 2 : /* POSIX cat */
      i18n_include_input->value("<nl_types.h>");
      i18n_file_input->value("");
      i18n_file = i18n_file_input->value();
      i18n_set_input->value("1");
      i18n_set = i18n_set_input->value();
      i18n_include_input->show();
      i18n_include = i18n_include_input->value();
      i18n_file_input->show();
      i18n_set_input->show();
      i18n_function_input->hide();
      break;
  }

  set_modflag(1);
}

void i18n_text_cb(fltk3::Input *i, void *) {
  undo_checkpoint();
  
  if (i == i18n_function_input)
    i18n_function = i->value();
  else if (i == i18n_file_input)
    i18n_file = i->value();
  else if (i == i18n_include_input)
    i18n_include = i->value();
  
  set_modflag(1);
}

void i18n_int_cb(fltk3::IntInput *i, void *) {
  undo_checkpoint();
  
  if (i == i18n_set_input)
    i18n_set = i->value();
  
  set_modflag(1);
}

extern const char* header_file_name;
extern const char* code_file_name;

void show_project_cb(fltk3::Widget *, void *) {
  if(project_window==0) make_project_window();
  include_H_from_C_button->value(include_H_from_C);
  use_FL_COMMAND_button->value(use_FL_COMMAND);
  header_file_input->value(header_file_name);
  code_file_input->value(code_file_name);
  i18n_type_chooser->value(i18n_type);
  i18n_function_input->value(i18n_function);
  i18n_file_input->value(i18n_file);
  i18n_set_input->value(i18n_set);
  i18n_include_input->value(i18n_include);
  switch (i18n_type) {
  case 0 : /* None */
      i18n_include_input->hide();
      i18n_file_input->hide();
      i18n_set_input->hide();
      i18n_function_input->hide();
      break;
  case 1 : /* GNU gettext */
      i18n_include_input->show();
      i18n_file_input->hide();
      i18n_set_input->hide();
      i18n_function_input->show();
      break;
  case 2 : /* POSIX cat */
      i18n_include_input->show();
      i18n_file_input->show();
      i18n_set_input->show();
      i18n_function_input->hide();
      break;
  }
  project_window->hotspot(project_window);
  project_window->show();
}

void show_grid_cb(fltk3::Widget *, void *) {
  char buf[128];
  sprintf(buf,"%d",gridx); horizontal_input->value(buf);
  sprintf(buf,"%d",gridy); vertical_input->value(buf);
  sprintf(buf,"%d",snap); snap_input->value(buf);
  guides_toggle->value(show_guides);
  int s = Fl_Widget_Type::default_size;
  if (s<=8) def_widget_size[0]->setonly();
  else if (s<=11) def_widget_size[1]->setonly();
  else if (s<=14) def_widget_size[2]->setonly();
  else if (s<=18) def_widget_size[3]->setonly();
  else if (s<=24) def_widget_size[4]->setonly();
  else if (s<=32) def_widget_size[5]->setonly();
  grid_window->hotspot(grid_window);
  grid_window->show();
}

void show_settings_cb(fltk3::Widget *, void *) {
  settings_window->hotspot(settings_window);
  settings_window->show();
}

void show_global_settings_cb(fltk3::Widget *, void *) {
  global_settings_window->hotspot(global_settings_window);
  show_global_settings_window();
}

void header_input_cb(fltk3::Input* i, void*) {
  if (header_file_name && strcmp(header_file_name, i->value()))
    set_modflag(1);
  header_file_name = i->value();
}
void code_input_cb(fltk3::Input* i, void*) {
  if (code_file_name && strcmp(code_file_name, i->value()))
    set_modflag(1);
  code_file_name = i->value();
}

void include_H_from_C_button_cb(fltk3::CheckButton* b, void*) {
  if (include_H_from_C != b->value()) {
    set_modflag(1);
    include_H_from_C = b->value();
  }
}

void use_FL_COMMAND_button_cb(fltk3::CheckButton* b, void*) {
  if (use_FL_COMMAND != b->value()) {
    set_modflag(1);
    use_FL_COMMAND = b->value();
  }
}

////////////////////////////////////////////////////////////////

fltk3::MenuItem window_type_menu[] = {
  {"Single",0,0,(void*)fltk3::WINDOW},
  {"Double",0,0,(void*)(fltk3::WINDOW+1)},
  {0}};

static int overlays_invisible;

// The following fltk3::Widget is used to simulate the windows.  It has
// an overlay for the fluid ui, and special-cases the fltk3::NO_BOX.

class Overlay_Window : public fltk3::OverlayWindow {
  void draw();
  void draw_overlay();
public:
  Fl_Window_Type *window;
  int handle(int);
  Overlay_Window(int W,int H) : fltk3::OverlayWindow(W,H) {fltk3::Group::current(0);}
  void resize(int,int,int,int);
  uchar *read_image(int &ww, int &hh);
};

void Overlay_Window::draw() {
  const int CHECKSIZE = 8;
  // see if box is clear or a frame or rounded:
  if ((damage()&fltk3::DAMAGE_ALL) &&
      (!box() || (box()>=4&&!(box()&2)) || box()>=fltk3::ROUNDED_BOX)) {
    // if so, draw checkerboard so user can see what areas are clear:
    for (int Y = 0; Y < h(); Y += CHECKSIZE) 
      for (int X = 0; X < w(); X += CHECKSIZE) {
	fltk3::color(((Y/(2*CHECKSIZE))&1) != ((X/(2*CHECKSIZE))&1) ?
		 fltk3::WHITE : fltk3::BLACK);
	fltk3::rectf(X,Y,CHECKSIZE,CHECKSIZE);
      }
  }
  OverlayWindow::draw();
}

extern fltk3::Window *main_window;

// Read an image of the overlay window
uchar *Overlay_Window::read_image(int &ww, int &hh) {
  // Create an off-screen buffer for the window...
  //main_window->make_current();
  make_current();

  ww = w();
  hh = h();

  fltk3::Offscreen offscreen = fl_create_offscreen(ww, hh);
  uchar *pixels;

  // Redraw the window into the offscreen buffer...
  fl_begin_offscreen(offscreen);

  if (!shown()) image(fltk3::scheme_bg_);

  redraw();
  draw();

  // Read the screen image...
  pixels = fltk3::read_image(0, 0, 0, ww, hh);

  fl_end_offscreen();

  // Cleanup and return...
  fl_delete_offscreen(offscreen);
  main_window->make_current();
  return pixels;
}

void Overlay_Window::draw_overlay() {
  window->draw_overlay();
}
int Overlay_Window::handle(int e) {
  int ret =  window->handle(e);
  if (ret==0) {
    switch (e) {
      case fltk3::SHOW:
      case fltk3::HIDE:
        ret = OverlayWindow::handle(e);
    }
  }
  return ret;
}

Fl_Type *Fl_Window_Type::make() {
  Fl_Type *p = Fl_Type::current;
  while (p && !p->is_code_block()) p = p->parent;
  if (!p) {
    fltk3::message("Please select a function");
    return 0;
  }
  Fl_Window_Type *myo = new Fl_Window_Type();
  if (!this->o) {// template widget
    this->o = new fltk3::Window(100,100);
    fltk3::Group::current(0);
  }
  // Set the size ranges for this window; in order to avoid opening the
  // X display we use an arbitrary maximum size...
  ((fltk3::Window *)(this->o))->size_range(gridx, gridy,
                                       3072, 2048,
                                       gridx, gridy, 0);
  myo->factory = this;
  myo->pDragMode = 0;
  myo->pNumSelected = 0;
  Overlay_Window *w = new Overlay_Window(100,100);
  w->window = myo;
  myo->o = w;
  myo->add(p);
  myo->pIsModal = 0;
  myo->pIsNonModal = 0;
  return myo;
}

void Fl_Window_Type::add_child(Fl_Type* cc, Fl_Type* before) {
  if (!cc->is_widget()) return;
  Fl_Widget_Type* c = (Fl_Widget_Type*)cc;
  fltk3::Widget* b = before ? ((Fl_Widget_Type*)before)->o : 0;
  ((fltk3::Window*)o)->insert(*(c->o), b);
  o->redraw();
}

void Fl_Window_Type::remove_child(Fl_Type* cc) {
  Fl_Widget_Type* c = (Fl_Widget_Type*)cc;
  ((fltk3::Window*)o)->remove(c->o);
  o->redraw();
}

void Fl_Window_Type::move_child(Fl_Type* cc, Fl_Type* before) {
  Fl_Widget_Type* c = (Fl_Widget_Type*)cc;
  ((fltk3::Window*)o)->remove(c->o);
  fltk3::Widget* b = before ? ((Fl_Widget_Type*)before)->o : 0;
  ((fltk3::Window*)o)->insert(*(c->o), b);
  o->redraw();
}

////////////////////////////////////////////////////////////////

// Double-click on window widget shows the window, or if already shown,
// it shows the control panel.
void Fl_Window_Type::open() {
  Overlay_Window *w = (Overlay_Window *)o;
  if (w->shown()) {
    w->show();
    Fl_Widget_Type::open();
  } else {
    fltk3::Widget *p = w->resizable();
    if (!p) w->resizable(w);
    w->show();
    w->resizable(p);
  }

  w->image(fltk3::scheme_bg_);
  w->size_range(gridx, gridy, fltk3::w(), fltk3::h(), gridx, gridy, 0);
}

// Read an image of the window
uchar *Fl_Window_Type::read_image(int &ww, int &hh) {
  Overlay_Window *w = (Overlay_Window *)o;

  // Read the screen image...
  return (w->read_image(ww, hh));
}


// control panel items:

void modal_cb(fltk3::LightButton* i, void* v) {
  if (v == Fl_Panel::LOAD) {
    if (!Fl_Panel::current->is_window()) {i->hide(); return;}
    i->show();
    i->value(((Fl_Window_Type *)Fl_Panel::current_widget())->pIsModal);
  } else {
    ((Fl_Window_Type *)Fl_Panel::current_widget())->pIsModal = i->value();
    set_modflag(1);
  }
}

void non_modal_cb(fltk3::LightButton* i, void* v) {
  if (v == Fl_Panel::LOAD) {
    if (!Fl_Panel::current->is_window()) {i->hide(); return;}
    i->show();
    i->value(((Fl_Window_Type *)Fl_Panel::current_widget())->pIsNonModal);
  } else {
    ((Fl_Window_Type *)Fl_Panel::current_widget())->pIsNonModal = i->value();
    set_modflag(1);
  }
}

void border_cb(fltk3::LightButton* i, void* v) {
  if (v == Fl_Panel::LOAD) {
    if (!Fl_Panel::current->is_window()) {i->hide(); return;}
    i->show();
    i->value(((fltk3::Window*)(Fl_Panel::current_widget()->o))->border());
  } else {
    ((fltk3::Window*)(Fl_Panel::current_widget()->o))->border(i->value());
    set_modflag(1);
  }
}

void xclass_cb(fltk3::Input* i, void* v) {
  if (v == Fl_Panel::LOAD) {
    if (!Fl_Panel::current->is_window()) {
      i->hide(); 
      i->parent()->hide(); // hides the "X Class:" label as well
      return;
    }
    i->show();
    i->parent()->show();
    i->value(((Fl_Widget_Type *)Fl_Panel::current_widget())->xclass);
  } else {
    int mod = 0;
    for (Fl_Type *o = Fl_Type::first; o; o = o->next) {
      if (o->selected && o->is_widget()) {
        mod = 1;
	Fl_Widget_Type* w = (Fl_Widget_Type*)o;
	if (w->is_window() || w->is_button())
	  storestring(i->value(),w->xclass);
	if (w->is_window()) ((fltk3::Window*)(w->o))->xclass(w->xclass);
	else if (w->is_menu_item()) w->redraw();
      }
    }
    if (mod) set_modflag(1);
  }
}

////////////////////////////////////////////////////////////////

void Fl_Window_Type::setlabel(const char *n) {
  if (o) ((fltk3::Window *)o)->label(n);
}

// make() is called on this widget when user picks window off New menu:
Fl_Window_Type Fl_Window_type;

// Resize from window manager...
void Overlay_Window::resize(int X,int Y,int W,int H) {
  fltk3::Widget* t = resizable(); resizable(0);

  // do not set the mod flag if the window was not resized. In FLUID, all
  // windows are opened without a given x/y position, so modifying x/y
  // should not mark the project as dirty
  if (W!=w() || H!=h())
    set_modflag(1);

  OverlayWindow::resize(X,Y,W,H);
  resizable(t);
  update_xywh();
}


/*
 * Calculate actual move by moving mouse position (mx,my) to
 * nearest multiple of gridsize, and snap to original position.
 */
void Fl_Window_Type::handle_drag_event() 
{
  int mydx, mydy;
  
  // -- handle mouse pointer snapping
  if (fltk3::event_state(fltk3::ALT) || !snap) {
    // -- no snap size set, or ALT held down
    mydx = pCurrentMouseX-pInitialMouseX;
    mydy = pCurrentMouseY-pInitialMouseY;
    if (abs(mydx) < 2 && abs(mydy) < 2) 
      mydx = mydy = 0;
  } else {
    // -- set mydx and mydy 
    int dx0 = pCurrentMouseX-pInitialMouseX;
    int ix = (pDragMode&RIGHT) ? pSelectionBox.r() : pSelectionBox.x();
    mydx = gridx ? ((ix+dx0+gridx/2)/gridx)*gridx - ix : dx0;
    if (dx0 > snap) {
      if (mydx < 0) mydx = 0;
    } else if (dx0 < -snap) {
      if (mydx > 0) mydx = 0;
    } else 
      mydx = 0;
    int dy0 = pCurrentMouseY-pInitialMouseY;
    int iy = (pDragMode&BOTTOM) ? pSelectionBox.y() : pSelectionBox.b();
    mydy = gridy ? ((iy+dy0+gridy/2)/gridy)*gridy - iy : dy0;
    if (dy0 > snap) {
      if (mydy < 0) mydy = 0;
    } else if (dy0 < -snap) {
      if (mydy > 0) mydy = 0;
    } else 
      mydy = 0;
  }

  if (!(pDragMode & (DRAG | BOX | LEFT | RIGHT))) {
    mydx = 0;
    pDeltaX = 0;
  }

  if (!(pDragMode & (DRAG | BOX | TOP | BOTTOM))) {
    mydy = 0;
    pDeltaY = 0;
  }
  
  if (pDeltaX != mydx || pDeltaY != mydy) {
    pDeltaX = mydx; pDeltaY = mydy;
    ((Overlay_Window *)o)->redraw_overlay();
  }
}


/*
 * Move a widget according to pDeltaX and pDeltaY calculated above
 */
void Fl_Window_Type::newposition(Fl_Widget_Type *myo,int &X,int &Y,int &R,int &T) {
  X = myo->o->dx_window();
  Y = myo->o->dy_window();
  R = X+myo->o->w();
  T = Y+myo->o->h();
  if (!pDragMode) return;
  if (pDragMode&DRAG) {
    X += pDeltaX;
    Y += pDeltaY;
    R += pDeltaX;
    T += pDeltaY;
  } else {
    if (pDragMode&LEFT) {
      if (X==pSelectionBox.x()) {
        X += pDeltaX; 
      } else {
        if (X<pSelectionBox.x()+pDeltaX) X = pSelectionBox.x()+pDeltaX;
      }
    }
    if (pDragMode&TOP) {
      if (Y==pSelectionBox.y()) {
        Y += pDeltaY;
      } else {
        if (Y<pSelectionBox.y()+pDeltaY) Y = pSelectionBox.y()+pDeltaY;
      }
    }
    if (pDragMode&RIGHT) {
      if (R==pSelectionBox.r()) {
        R += pDeltaX; 
      } else {
        if (R>pSelectionBox.r()+pDeltaX) R = pSelectionBox.r()+pDeltaX;
      }
    }
    if (pDragMode&BOTTOM) {
      if (T==pSelectionBox.b()) {
        T += pDeltaY; 
      } else {
        if (T>pSelectionBox.b()+pDeltaX) T = pSelectionBox.b()+pDeltaX;
      }
    }
  }
  if (R<X) {int n = X; X = R; R = n;}
  if (T<Y) {int n = Y; Y = T; T = n;}
}


// draw a vertical arrow pointing toward y2
static void draw_v_arrow(int x, int y1, int y2) {
  int dy = (y1>y2) ? -1 : 1 ;
  fltk3::yxline(x, y1, y2);
  fltk3::xyline(x-4, y2, x+4);
  fltk3::line(x-2, y2-dy*5, x, y2-dy);
  fltk3::line(x+2, y2-dy*5, x, y2-dy);
}

static void draw_h_arrow(int x1, int y, int x2) {
  int dx = (x1>x2) ? -1 : 1 ;
  fltk3::xyline(x1, y, x2);
  fltk3::yxline(x2, y-4, y+4);
  fltk3::line(x2-dx*5, y-2, x2-dx, y);
  fltk3::line(x2-dx*5, y+2, x2-dx, y);
}

static void draw_top_brace(const fltk3::Widget *w) {
  fltk3::yxline(w->x(), w->y()-2, w->y()+6);
  fltk3::yxline(w->x()+w->w()-1, w->y()-2, w->y()+6);
  fltk3::xyline(w->x()-2, w->y(), w->x()+w->w()+1);
}

static void draw_left_brace(const fltk3::Widget *w) {
  fltk3::xyline(w->x()-2, w->y(), w->x()+6);
  fltk3::xyline(w->x()-2, w->y()+w->h()-1, w->x()+6);
  fltk3::yxline(w->x(), w->y()-2, w->y()+w->h()+1);
}

static void draw_right_brace(const fltk3::Widget *w) {
  int xx = w->x() + w->w() - 1;
  fltk3::xyline(xx-6, w->y(), xx+2);
  fltk3::xyline(xx-6, w->y()+w->h()-1, xx+2);
  fltk3::yxline(xx, w->y()-2, w->y()+w->h()+1);
}

static void draw_bottom_brace(const fltk3::Widget *w) {
  int yy = w->y() + w->h() - 1;
  fltk3::yxline(w->x(), yy-6, yy+2);
  fltk3::yxline(w->x()+w->w()-1, yy-6, yy+2);
  fltk3::xyline(w->x()-2, yy, w->x()+w->w()+1);
}

static void draw_height(int x, int y, int b, fltk3::Align a) {
  char buf[16];
  int h = b - y;
  sprintf(buf, "%d", h);
  fltk3::font(fltk3::HELVETICA, 9);
  int lw = (int)fltk3::width(buf);
  int lx;

  b --;
  if (h < 30) {
    // Move height to the side...
    if (a == fltk3::ALIGN_LEFT) lx = x - lw - 2;
    else lx = x + 2;

    fltk3::yxline(x, y, b);
  } else {
    // Put height inside the arrows...
    lx = x - lw / 2;

    fltk3::yxline(x, y, y + (h - 11) / 2);
    fltk3::yxline(x, y + (h + 11) / 2, b);
  }

  // Draw the height...
  fltk3::draw(buf, lx, y + (h + 9) / 2);

  // Draw the arrowheads...
  fltk3::line(x-2, y+5, x, y+1, x+2, y+5);
  fltk3::line(x-2, b-5, x, b-1, x+2, b-5);

  // Draw the end lines...
  fltk3::xyline(x - 4, y, x + 4);
  fltk3::xyline(x - 4, b, x + 4);
}

static void draw_width(int x, int y, int r, fltk3::Align a) {
  char buf[16];
  int w = r-x;
  sprintf(buf, "%d", w);
  fltk3::font(fltk3::HELVETICA, 9);
  int lw = (int)fltk3::width(buf);
  int ly = y + 4;

  r --;

  if (lw > (w - 20)) {
    // Move width above/below the arrows...
    if (a == fltk3::ALIGN_TOP) ly -= 10;
    else ly += 10;

    fltk3::xyline(x, y, r);
  } else {
    // Put width inside the arrows...
    fltk3::xyline(x, y, x + (w - lw - 2) / 2);
    fltk3::xyline(x + (w + lw + 2) / 2, y, r);
  }

  // Draw the width...
  fltk3::draw(buf, x + (w - lw) / 2, ly);

  // Draw the arrowheads...
  fltk3::line(x+5, y-2, x+1, y, x+5, y+2);
  fltk3::line(r-5, y-2, r-1, y, r-5, y+2);

  // Draw the end lines...
  fltk3::yxline(x, y - 4, y + 4);
  fltk3::yxline(r, y - 4, y + 4);
}

void Fl_Window_Type::draw_overlay() {
  if (pRecalculateSelectionBox) {
    pSelectionBox.x(o->w()); pSelectionBox.y(o->h()); pSelectionBox.set_r(0); pSelectionBox.set_b(0);
    pNumSelected = 0;
    for (Fl_Type *q=next; q && q->level>level; q=q->next)
      if (q->selected && q->is_widget() && !q->is_menu_item()) {
	pNumSelected++;
	Fl_Widget_Type* myo = (Fl_Widget_Type*)q;
        int myo_x = myo->o->dx_window();
        int myo_y = myo->o->dy_window();
	if (myo_x < pSelectionBox.x()) pSelectionBox.x(myo_x);
	if (myo_y < pSelectionBox.y()) pSelectionBox.y(myo_y);
	if (myo_x+myo->o->w() > pSelectionBox.r()) pSelectionBox.set_r(myo_x+myo->o->w());
	if (myo_y+myo->o->h() > pSelectionBox.b()) pSelectionBox.set_b(myo_y+myo->o->h());
      }
    pRecalculateSelectionBox = 0;
  }
  fltk3::color(fltk3::RED);
  if (pDragMode==BOX && (pInitialMouseX != pCurrentMouseX || pInitialMouseY != pCurrentMouseY)) {
    int x = pInitialMouseX; int r = pCurrentMouseX; if (x > r) {x = pCurrentMouseX; r = pInitialMouseX;}
    int y = pInitialMouseY; int b = pCurrentMouseY; if (y > b) {y = pCurrentMouseY; b = pInitialMouseY;}
    fltk3::rect(x,y,r-x,b-y);
  }
  if (overlays_invisible && !pDragMode) return;
  if (selected) fltk3::rect(0,0,o->w(),o->h());
  if (!pNumSelected) return;
  int mybx,myby,mybr,mybt;
  int mysx,mysy,mysr,myst;
  mybx = mysx = o->w(); myby = mysy = o->h(); mybr = mysr = 0; mybt = myst = 0;
  Fl_Type *selection = 0L; // used to store the one selected widget (if n==1)
  for (Fl_Type *q=next; q && q->level>level; q = q->next)
    if (q->selected && q->is_widget() && !q->is_menu_item()) {
      selection = q;
      Fl_Widget_Type* myo = (Fl_Widget_Type*)q;
      int x,y,r,t;
      newposition(myo,x,y,r,t);
      if (!show_guides || !pDragMode || pNumSelected != 1) fltk3::rect(x,y,r-x,t-y);
      if (x < mysx) mysx = x;
      if (y < mysy) mysy = y;
      if (r > mysr) mysr = r;
      if (t > myst) myst = t;
      if (!(myo->o->align() & fltk3::ALIGN_INSIDE)) {
        // Adjust left/right/top/bottom for top/bottom labels...
	int ww, hh;
	ww = (myo->o->align() & fltk3::ALIGN_WRAP) ? myo->o->w() : 0;
	hh = myo->o->labelsize();
	myo->o->measure_label(ww, hh);
	if (myo->o->align() & fltk3::ALIGN_TOP) y -= hh;
	else if (myo->o->align() & fltk3::ALIGN_BOTTOM) t += hh;
	else if (myo->o->align() & fltk3::ALIGN_LEFT) x -= ww + 4;
	else if (myo->o->align() & fltk3::ALIGN_RIGHT) r += ww + 4;
      }
      if (x < mybx) mybx = x;
      if (y < myby) myby = y;
      if (r > mybr) mybr = r;
      if (t > mybt) mybt = t;
    }
  if (selected) return;

  if (show_guides && pDragMode) {
    // draw overlays for UI Guideline distances
    // - check for distance to the window edge
    //    * FLTK suggests 10 pixels from the edge
    int d;
    int xsp, ysp;
    int mybx_bak = mybx, myby_bak = myby, mybr_bak = mybr, mybt_bak = mybt;
    Fl_Widget_Type *mysel = (Fl_Widget_Type *)selection;


    ideal_spacing(xsp, ysp);

    if (pDragMode) {
      // Check top spacing...
      if (abs(d = myby - ysp) < 3) {
	pDeltaY -= d;
	if (pDragMode & DRAG) mybt -= d;
	myby -= d;
	draw_v_arrow(mybx+5, myby, 0);
      }

      // Check bottom spacing...
      if (abs(d = o->h() - mybt - ysp) < 3) {
	pDeltaY += d;
	if (pDragMode & DRAG) myby += d;
	mybt += d;
	draw_v_arrow(mybx+5, mybt, o->h());
      }

      // Check left spacing...
      if (abs(d = mybx - xsp) < 3) {
        pDeltaX -= d;
	if (pDragMode & DRAG) mybr -= d;
	mybx -= d;
	draw_h_arrow(mybx, myby+5, 0);
      }

      // Check right spacing...
      if (abs(d = o->w() - mybr - xsp) < 3) {
	pDeltaX += d;
	if (pDragMode & DRAG) mybx += d;
	mybr += d;
	draw_h_arrow(mybr, myby+5, o->w());
      }
    }

    if (pNumSelected==1 && selection && !(pDragMode & DRAG)) {
      // Check ideal sizes
      int x,y,r,t;
      newposition(mysel,x,y,r,t);
      int w = r-x;
      int h = t-y;
      int iw = w, ih = h;

      mysel->ideal_size(iw, ih);

      if (pDragMode & (TOP | BOTTOM)) {
	// Check height
	if (abs(d = ih - h) < 5) {
          // Resize height
	  if (pDragMode & TOP) {
	    myby -= d;
	    y -= d;
	    pDeltaY -= d;
	  } else {
	    mybt += d;
	    t += d;
	    pDeltaY += d;
	  }
	}

	// Draw height guide
	draw_height(x < 50 ? x+10 : x-10, y, t,
	            x < 50 ? fltk3::ALIGN_RIGHT : fltk3::ALIGN_LEFT);
      }

      if (pDragMode & (LEFT | RIGHT)) {
	// Check width
	if (abs(d = iw - w) < 5) {
          // Resize width
          if (pDragMode & LEFT) {
	    mybx -= d;
	    x -= d;
	    pDeltaX -= d;
	  } else {
	    mybr += d;
	    r += d;
	    pDeltaX += d;
	  }
	}

	// Draw width guide
	draw_width(x, y < 50 ? y+10 : y-10, r,
	           y < 50 ? fltk3::ALIGN_BOTTOM : fltk3::ALIGN_TOP);
      }
    }

    // Check spacing and alignment between individual widgets
    if (pDragMode && selection->is_widget()) {
      for (Fl_Type *q=next; q && q->level>level; q = q->next)
	if (q != selection && q->is_widget()) {
          Fl_Widget_Type *qw = (Fl_Widget_Type*)q;
          // Only check visible widgets...
	  if (!qw->o->visible_r()) continue;

          // Get bounding box of widget...
	  int qx = qw->o->dx_window();
	  int qr = qx + qw->o->w();
	  int qy = qw->o->dy_window();
	  int qt = qy + qw->o->h();

	  if (!(qw->o->align() & fltk3::ALIGN_INSIDE)) {
            // Adjust top/bottom for top/bottom labels...
	    int ww, hh;
	    ww = qw->o->w();
	    hh = qw->o->labelsize();
	    qw->o->measure_label(ww, hh);
	    if (qw->o->align() & fltk3::ALIGN_TOP) qy -= hh;
	    if (qw->o->align() & fltk3::ALIGN_BOTTOM) qt += hh;
	  }

          // Do horizontal alignment when the widget is within 25
	  // pixels vertically...
	  if (fl_min(abs(qy - mysel->o->y() - mysel->o->h()),
	             abs(mysel->o->y() - qt)) < 25) {
            // Align to left of other widget...
            if ((pDragMode & (LEFT | DRAG)) && abs(d = mybx - qx) < 3) {
	      pDeltaX += d;
              mybx += d;
	      if (pDragMode & DRAG) mybr += d;

	      draw_left_brace(qw->o);
	    }

            // Align to right of other widget...
            if ((pDragMode & (RIGHT | DRAG)) &&
	        abs(d = qr - mybr) < 3) {
	      pDeltaX += d;
              if (pDragMode & DRAG) mybx += d;
	      mybr += d;

	      draw_right_brace(qw->o);
	    }
          }

          // Align to top of other widget...
          if ((pDragMode & (TOP | DRAG)) && abs(d = myby - qy) < 3) {
	    pDeltaY += d;
            myby += d;
	    if (pDragMode & DRAG) mybt += d;

	    draw_top_brace(qw->o);
	  }

          // Align to bottom of other widget...
          if ((pDragMode & (BOTTOM | DRAG)) && abs(d = qt - mybt) < 3) {
	    pDeltaY += d;
            if (pDragMode & DRAG) myby += d;
	    mybt += d;

	    draw_bottom_brace(qw->o);
	  }

          // Check spacing between widgets
	  if (mysel->is_group()) mysel->ideal_spacing(xsp, ysp);
          else qw->ideal_spacing(xsp, ysp);

          if ((qt)>=myby && qy<=mybt) {
            if (pDragMode & (LEFT | DRAG)) {
	      // Compare left of selected to left of current
	      if (abs(d = qx - mybx - xsp) >= 3)
	        d = qx - mybx + xsp;

	      if (abs(d) < 3) {
		pDeltaX += d;
        	mybx += d;
		if (pDragMode & DRAG) mybr += d;

        	// Draw left arrow
		draw_h_arrow(mybx, (myby+mybt)/2, qx);
              }

	      // Compare left of selected to right of current
              if (abs(d = qr - mybx - xsp) >= 3)
	        d = qr - mybx + xsp;

	      if (abs(d) < 3) {
		pDeltaX += d;
        	mybx += d;
		if (pDragMode & DRAG) mybr += d;

        	// Draw left arrow
		draw_h_arrow(mybx, (myby+mybt)/2, qr);
              }
	    }

            if (pDragMode & (RIGHT | DRAG)) {
	      // Compare right of selected to left of current
	      if (abs(d = qx - mybr - xsp) >= 3)
	        d = qx - mybr + xsp;

	      if (abs(d) < 3) {
		pDeltaX += d;
        	if (pDragMode & DRAG) mybx += d;
		mybr += d;

        	// Draw right arrow
		draw_h_arrow(mybr, (myby+mybt)/2, qx);
              }

	      // Compare right of selected to right of current
              if (abs(d = qr - mybr + xsp) >= 3)
	        d = qr - mybr - xsp;

              if (abs(d) < 3) {
		pDeltaX += d;
        	if (pDragMode & DRAG) mybx += d;
		mybr += d;

        	// Draw right arrow
		draw_h_arrow(mybr, (myby+mybt)/2, qr);
              }
            }
	  }

          if (qr>=mybx && qx<=mybr) {
            // Compare top of selected to top of current
            if (pDragMode & (TOP | DRAG)) {
	      if (abs(d = qy - myby - ysp) >= 3)
	        d = qy - myby + ysp;

	      if (abs(d) < 3) {
		pDeltaY += d;
		myby += d;
		if (pDragMode & DRAG) mybt += d;

		// Draw up arrow...
		draw_v_arrow((mybx+mybr)/2, myby, qy);
              }

              // Compare top of selected to bottom of current
              if (abs(d = qt - myby - ysp) >= 3)
                d = qt - myby + ysp;

              if (abs(d) < 3) {
		pDeltaY += d;
		myby += d;
		if (pDragMode & DRAG) mybt += d;

		// Draw up arrow...
		draw_v_arrow((mybx+mybr)/2, myby, qt);
              }
	    }

	    // Compare bottom of selected to top of current
            if (pDragMode & (BOTTOM | DRAG)) {
	      if (abs(d = qy - mybt - ysp) >= 3)
	        d = qy - mybt + ysp;

	      if (abs(d) < 3) {
		pDeltaY += d;
		if (pDragMode & DRAG) myby += d;
		mybt += d;

		// Draw down arrow...
		draw_v_arrow((mybx+mybr)/2, mybt, qy);
              }

	      // Compare bottom of selected to bottom of current
              if (abs(d = qt - mybt - ysp) >= 3)
                d = qt - mybt + ysp;

              if (abs(d) < 3) {
		pDeltaY += d;
		if (pDragMode & DRAG) myby += d;
		mybt += d;

		// Draw down arrow...
		draw_v_arrow((mybx+mybr)/2, mybt, qt);
              }
	    }
          }
	}
    }
    mysx += mybx-mybx_bak; mysr += mybr-mybr_bak;
    mysy += myby-myby_bak; myst += mybt-mybt_bak;
  }
  // Draw selection box + resize handles...
  // draw box including all labels
  fltk3::line_style(fltk3::DOT);
  fltk3::rect(mybx,myby,mybr-mybx,mybt-myby);
  fltk3::line_style(fltk3::SOLID);
  // draw box excluding labels
  fltk3::rect(mysx,mysy,mysr-mysx,myst-mysy);
  fltk3::rectf(mysx,mysy,5,5);
  fltk3::rectf(mysr-5,mysy,5,5);
  fltk3::rectf(mysr-5,myst-5,5,5);
  fltk3::rectf(mysx,myst-5,5,5);
}

extern fltk3::MenuItem Main_Menu[];

// Calculate new bounding box of selected widgets:
void Fl_Window_Type::fix_overlay() {
  Main_Menu[40].label("Hide O&verlays");
  overlays_invisible = 0;
  pRecalculateSelectionBox = 1;
  ((Overlay_Window *)(this->o))->redraw_overlay();
}

// check if we must redraw any parent of tabs/wizard type
void check_redraw_corresponding_parent(Fl_Type *s) {
    Fl_Widget_Type * prev_parent = 0;
    if( !s || !s->selected || !s->is_widget()) return;
    for (Fl_Type *i=s; i && i->parent; i=i->parent) {
	if (i->is_group() && prev_parent && 
	    (!strcmp(i->type_name(), "fltk3::TabGroup") || 
	     !strcmp(i->type_name(), "fltk3::WizardGroup"))) {
	     ((fltk3::TabGroup*)((Fl_Widget_Type*)i)->o)->value(prev_parent->o);
	     return;
	}
	if (i->is_group() && s->is_widget()) 
	    prev_parent = (Fl_Widget_Type*)i;
    }
}
 
// do that for every window (when selected set changes):
void redraw_overlays() {
  for (Fl_Type *o=Fl_Type::first; o; o=o->next)
    if (o->is_window()) ((Fl_Window_Type*)o)->fix_overlay();
}

void toggle_overlays(fltk3::Widget *,void *) {
  overlays_invisible = !overlays_invisible;

  if (overlays_invisible) Main_Menu[40].label("Show O&verlays");
  else Main_Menu[40].label("Hide O&verlays");

  for (Fl_Type *o=Fl_Type::first; o; o=o->next)
    if (o->is_window()) {
      Fl_Widget_Type* w = (Fl_Widget_Type*)o;
      ((Overlay_Window*)(w->o))->redraw_overlay();
    }
}

extern void select(Fl_Type *,int);
extern void select_only(Fl_Type *);
extern void deselect();
extern Fl_Type* in_this_only;
extern void fix_group_size(Fl_Type *t);

extern fltk3::MenuItem Main_Menu[];
extern fltk3::MenuItem New_Menu[];


/*
 * Move the selected children according to current pDeltaX, pDeltaY, and 
 * pDragMode state:
 */
void Fl_Window_Type::move_all_children()
{
  undo_checkpoint();
  Fl_Type *i;
  for (i=next; i && i->level>level;) {
    if (i->selected && i->is_widget() && !i->is_menu_item()) {
      Fl_Widget_Type* myo = (Fl_Widget_Type*)i;
      int x,y,r,t, hx=0, hy=0;
      newposition(myo,x,y,r,t);
      if (myo->parent && myo->parent->is_widget()) {
        Fl_Widget_Type *p = (Fl_Widget_Type*)myo->parent;
        hx = p->o->dx_window();
        hy = p->o->dy_window();
      }
      int dx = myo->o->x()-x+hx, dy = myo->o->y()-y+hy;
      myo->o->resize(x-hx,y-hy,r-x,t-y);
      // don't move any children, whether selected or not:
      Fl_Type* p;
      for (p = myo->next; p && p->level>myo->level; p = p->next) {
        if (pDragMode & (LEFT|TOP)) {
          if (p->is_widget() && !p->is_menu_item()) {
            Fl_Widget_Type* myo2 = (Fl_Widget_Type*)p;
            myo2->o->position(myo2->o->x()+dx, myo2->o->y()+dy);
          }
        }
      }
      i = p;
    } else {
      i = i->next;
    }
  }
  for (i=next; i && i->level>level; i=i->next) 
    fix_group_size(i);
  o->redraw();
  pRecalculateSelectionBox = 1;
  ((Overlay_Window *)(this->o))->redraw_overlay();
  set_modflag(1);
  pDeltaX = pDeltaY = 0;

  update_xywh();
}


/*
 * Handle all events to the preview window.
 */
int Fl_Window_Type::handle(int event) {
  
  static Fl_Type* selection;
  
  switch (event) {
      
    // User clicked in the window
    case fltk3::PUSH: {
      
      // -- store initial and current mouse position
      pInitialMouseX = pCurrentMouseX = fltk3::event_x();
      pInitialMouseY = pCurrentMouseY = fltk3::event_y();
      pDragMode = pDeltaX = pDeltaY = 0;
      
      // -- test for popup menu:
      if (fltk3::event_button() >= 3) {
        in_this_only = this; // modifies how some menu items work.
        static const fltk3::MenuItem* myprev;
        const fltk3::MenuItem* m = New_Menu->popup(pCurrentMouseX, pCurrentMouseY, "New", myprev);
        if (m && m->callback()) {
          myprev = m; 
          m->do_callback(this->o);
        }
        in_this_only = 0;
        return 1;
      }
      
      // -- find the innermost item clicked on:
      selection = this;
      for (Fl_Type* i=next; i && i->level>level; i=i->next) {
        if (i->is_widget() && !i->is_menu_item()) {
          Fl_Widget_Type* myo = (Fl_Widget_Type*)i;
          for (fltk3::Widget *o1 = myo->o; o1; o1 = o1->parent()) {
            if (!o1->visible()) 
              goto CONTINUE2;
          }
          if (fltk3::event_inside(myo->o->dx_window(), myo->o->dy_window(), myo->o->w(), myo->o->h())) {
            selection = myo;
            if (fltk3::event_clicks()==1)
              reveal_in_browser(myo);
          }
        CONTINUE2:;
        }
      }
      
      // -- see if user grabs edges of selected region:
      if (   pNumSelected 
          && !(fltk3::event_state(fltk3::SHIFT)) 
          && pCurrentMouseX<=pSelectionBox.r()+snap 
          && pCurrentMouseX>=pSelectionBox.x()-snap 
          && pCurrentMouseY<=pSelectionBox.b()+snap 
          && pCurrentMouseY>=pSelectionBox.y()-snap) 
      {
        int snap1 = snap>5 ? snap : 5;
        int w1 = (pSelectionBox.r()-pSelectionBox.x())/4; 
        if (w1 > snap1) 
          w1 = snap1;
        if (pCurrentMouseX>=pSelectionBox.r()-w1) 
          pDragMode |= RIGHT;
        else if (pCurrentMouseX<pSelectionBox.x()+w1) 
          pDragMode |= LEFT;
        w1 = (pSelectionBox.b()-pSelectionBox.y())/4; 
        if (w1 > snap1) 
          w1 = snap1;
        if (pCurrentMouseY<=pSelectionBox.y()+w1) 
          pDragMode |= TOP;
        else if (pCurrentMouseY>pSelectionBox.b()-w1) 
          pDragMode |= BOTTOM;
        if (!pDragMode) 
          pDragMode = DRAG;
      }
      
      // -- do object-specific selection of other objects:
      Fl_Type* t = selection->click_test(pCurrentMouseX, pCurrentMouseY);
      if (t) {
        //if (t == selection) return 1; // indicates mouse eaten w/o change
        if (fltk3::event_state(fltk3::SHIFT)) {
          fltk3::event_is_click(0);
          select(t, !t->selected);
        } else {
          deselect();
          select(t, 1);
          if (t->is_menu_item()) 
            t->open();
        }
        selection = t;
        pDragMode = 0;
      } else {
        if (!pDragMode) 
          pDragMode = BOX; // if all else fails, start a new selection region
      }
      return 1; }

    // User drags the mouse
    case fltk3::DRAG:
    
      // -- check if there is anything to do
      if (!pDragMode) 
        return 0;
      pCurrentMouseX = fltk3::event_x();
      pCurrentMouseY = fltk3::event_y();
      handle_drag_event();
      return 1;
      
      // user released mouse, show the results of the action
    case fltk3::RELEASE:
      
      // -- anything to do?
      if (!pDragMode) 
        return 0;
      pCurrentMouseX = fltk3::event_x();
      pCurrentMouseY = fltk3::event_y();
      
      if (pDragMode != BOX && (pDeltaX || pDeltaY || !fltk3::event_is_click())) {
        if (pDeltaX || pDeltaY) move_all_children();
      } else if ((fltk3::event_clicks() || fltk3::event_state(fltk3::CTRL))) {
        Fl_Widget_Type::open();
      } else {
        // -- apply the selection box
        if (pCurrentMouseX<pInitialMouseX) {int t = pInitialMouseX; pInitialMouseX = pCurrentMouseX; pCurrentMouseX = t;}
        if (pCurrentMouseY<pInitialMouseY) {int t = pInitialMouseY; pInitialMouseY = pCurrentMouseY; pCurrentMouseY = t;}
        int n = 0;
        int toggle = fltk3::event_state(fltk3::SHIFT);
        // clear selection on everything:
        if (!toggle) deselect(); else fltk3::event_is_click(0);
        // select everything in box:
        for (Fl_Type*i=next; i&&i->level>level; i=i->next)
          if (i->is_widget() && !i->is_menu_item()) {
            Fl_Widget_Type* myo = (Fl_Widget_Type*)i;
            for (fltk3::Widget *o1 = myo->o; o1; o1 = o1->parent())
              if (!o1->visible()) goto CONTINUE;
            if (fltk3::event_inside(myo->o->dx_window(), myo->o->dy_window(), myo->o->w(), myo->o->h())) 
              selection = myo;
            if (myo->o->dx_window()>=pInitialMouseX && myo->o->dy_window()>pInitialMouseY &&
                myo->o->dx_window()+myo->o->w()<pCurrentMouseX && myo->o->dy_window()+myo->o->h()<pCurrentMouseY) {
              n++;
              select(myo, toggle ? !myo->selected : 1);
            }
          CONTINUE:;
          }
        // if nothing in box, select what was clicked on:
        if (!n) {
          select(selection, toggle ? !selection->selected : 1);
        }
      }
      pDragMode = 0;
      ((Overlay_Window *)o)->redraw_overlay();
      return 1;
      
    case fltk3::KEYBOARD: {
      
      int backtab = 0;
      switch (fltk3::event_key()) {
          
        case fltk3::EscapeKey:
          ((fltk3::Window*)o)->hide();
          return 1;
          
        case fltk3::TabKey: {
          if (fltk3::event_state(fltk3::SHIFT)) backtab = 1;
          // find current child:
          Fl_Type *i = Fl_Type::current;
          while (i && (!i->is_widget() || i->is_menu_item())) i = i->parent;
          if (!i) return 0;
          Fl_Type *p = i->parent;
          while (p && p != this) p = p->parent;
          if (!p || !p->is_widget()) {
            i = next; if (!i || i->level <= level) return 0;
          }
          p = i;
          for (;;) {
            i = backtab ? i->prev : i->next;
            if (!i || i->level <= level) {i = p; break;}
            if (i->is_widget() && !i->is_menu_item()) break;
          }
          deselect(); select(i,1);
          return 1;}
          
        case fltk3::LeftKey:  pDeltaX = -1; pDeltaY = 0; goto ARROW;
        case fltk3::RightKey: pDeltaX = +1; pDeltaY = 0; goto ARROW;
        case fltk3::UpKey:    pDeltaX = 0; pDeltaY = -1; goto ARROW;
        case fltk3::DownKey:  pDeltaX = 0; pDeltaY = +1; goto ARROW;
        ARROW:
          // for some reason BOTTOM/TOP are swapped... should be fixed...
          pDragMode = (fltk3::event_state(fltk3::SHIFT)) ? (RIGHT|TOP) : DRAG;
          if (fltk3::event_state(fltk3::CTRL)) {pDeltaX *= gridx; pDeltaY *= gridy;}
          move_all_children();
          pDragMode = 0;
          return 1;
          
        case 'o':
          toggle_overlays(0, 0);
          break;
          
        default:
          return 0;
      }}
      
    case fltk3::SHORTCUT: {
      in_this_only = this; // modifies how some menu items work.
      const fltk3::MenuItem* m = Main_Menu->test_shortcut();
      if (m && m->callback()) m->do_callback(this->o);
      in_this_only = 0;
      return (m != 0);}
      
    default:
      return 0;
  }
}

////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "../src/fltk3/flstring.h"

void Fl_Window_Type::write_code1() {
  Fl_Widget_Type::write_code1();
}

void Fl_Window_Type::write_code2() {
  const char *var = is_class() ? "this" : name() ? name() : "o";
  write_extra_code();
  if (pIsModal) write_c("%s%s->set_modal();\n", indent(), var);
  else if (pIsNonModal) write_c("%s%s->set_non_modal();\n", indent(), var);
  if (!((fltk3::Window*)o)->border()) {
    write_c("%s%s->clear_border();\n", indent(), var);
  }
  if (xclass) {
    write_c("%s%s->xclass(", indent(), var);
    write_cstring(xclass);
    write_c(");\n");
  }
  if (pMaxW || pMaxH) {
    write_c("%s%s->size_range(%d, %d, %d, %d);\n", indent(), var,
            pMinW, pMinH, pMaxW, pMaxH);
  } else if (pMinW || pMinH) {
    write_c("%s%s->size_range(%d, %d);\n", indent(), var, pMinW, pMinH);
  }
  write_c("%s%s->end();\n", indent(), var);
  if (((fltk3::Window*)o)->resizable() == o)
    write_c("%s%s->resizable(%s);\n", indent(), var, var);
  write_block_close();
}

void Fl_Window_Type::write_properties() {
  Fl_Widget_Type::write_properties();
  if (pIsModal) write_string("modal");
  else if (pIsNonModal) write_string("non_modal");
  if (!((fltk3::Window*)o)->border()) write_string("noborder");
  if (xclass) {write_string("xclass"); write_word(xclass);}
  if (pMinW || pMinH || pMaxW || pMaxH)
    write_string("size_range {%d %d %d %d}", pMinW, pMinH, pMaxW, pMaxH);
  if (o->visible()) write_string("visible");
}

extern int pasteoffset;
char Fl_Window_Type::read_property(const char *c) {
  if (!strcmp(c,"modal")) {
    pIsModal = 1;
  } else if (!strcmp(c,"non_modal")) {
    pIsNonModal = 1;
  } else if (!strcmp(c, "visible")) {
    if (fltk3::first_window()) open(); // only if we are using user interface
  } else if (!strcmp(c,"noborder")) {
    ((fltk3::Window*)o)->border(0);
  } else if (!strcmp(c,"xclass")) {
    storestring(read_word(),xclass);
    ((fltk3::Window*)o)->xclass(xclass);
  } else if (!strcmp(c,"size_range")) {
    int mw, mh, MW, MH;
    if (sscanf(read_word(),"%d %d %d %d",&mw,&mh,&MW,&MH) == 4) {
      pMinW = mw; pMinH = mh; pMaxW = MW; pMaxH = MH;
    }
  } else if (!strcmp(c,"xywh")) {
    Fl_Widget_Type::read_property(c);
    pasteoffset = 0; // make it not apply to contents
  } else {
    return Fl_Widget_Type::read_property(c);
  }
  return 1;
}

///////////////////////////////////////////////////////////////////////

Fl_Widget_Class_Type Fl_Widget_Class_type;
Fl_Widget_Class_Type *current_widget_class = 0;

Fl_Type *Fl_Widget_Class_Type::make() {
  Fl_Type *p = Fl_Type::current;
  while (p && (!p->is_decl_block() || (p->is_widget() && p->is_class()))) p = p->parent;
  Fl_Widget_Class_Type *myo = new Fl_Widget_Class_Type();
  myo->name("UserInterface");

  if (!this->o) {// template widget
    this->o = new fltk3::Window(100,100);
    fltk3::Group::current(0);
  }
  // Set the size ranges for this window; in order to avoid opening the
  // X display we use an arbitrary maximum size...
  ((fltk3::Window *)(this->o))->size_range(gridx, gridy,
                                       3072, 2048,
                                       gridx, gridy, 0);
  myo->factory = this;
  myo->pDragMode = 0;
  myo->pNumSelected = 0;
  Overlay_Window *w = new Overlay_Window(100,100);
  w->window = myo;
  myo->o = w;
  myo->add(p);
  myo->pIsModal = 0;
  myo->pIsNonModal = 0;
  myo->wc_relative = 0;

  return myo;
}

void Fl_Widget_Class_Type::write_properties() {
  Fl_Window_Type::write_properties();
  if (wc_relative) write_string("position_relative");
}

char Fl_Widget_Class_Type::read_property(const char *c) {
  if (!strcmp(c,"position_relative")) {
    wc_relative = 1;
  } else {
    return Fl_Window_Type::read_property(c);
  }
  return 1;
}

// Convert A::B::C::D to D (i.e. keep only innermost name)
static const char *trimclassname(const char *n) {
  const char *nn;
  while((nn = strstr(n, "::"))) {
    n = nn + 2;
  }
  return(n);
}

void Fl_Widget_Class_Type::write_code1() {
#if 0
  Fl_Widget_Type::write_code1();
#endif // 0

  current_widget_class = this;
  write_public_state = 1;

  const char *c = subclass();
  if (!c) c = "fltk3::Group";

  write_h("\nclass %s : public %s {\n", name(), c);
  if (strstr(c, "Window")) {
    write_h("  void _%s();\n", trimclassname(name()));
    write_h("public:\n");
    write_h("  %s(int X, int Y, int W, int H, const char *L = 0);\n", trimclassname(name()));
    write_h("  %s(int W, int H, const char *L = 0);\n", trimclassname(name()));
    write_h("  %s();\n", trimclassname(name()));

    // a constructor with all four dimensions plus label
    write_c("%s::%s(int X, int Y, int W, int H, const char *L)\n", name(), trimclassname(name()));
    write_c("  : %s(X, Y, W, H, L) {\n", c);
    write_c("  _%s();\n", trimclassname(name()));
    write_c("}\n\n");

    // a constructor with just the size and label. The window manager will position the window
    write_c("%s::%s(int W, int H, const char *L)\n", name(), trimclassname(name()));
    write_c("  : %s(0, 0, W, H, L) {\n", c);
    write_c("  clear_flag(16);\n");
    write_c("  _%s();\n", trimclassname(name()));
    write_c("}\n\n");
    
    // a constructor that takes size and label from the Fluid database
    write_c("%s::%s()\n", name(), trimclassname(name()));
    write_c("  : %s(0, 0, %d, %d, ", c, o->w(), o->h());
    const char *cstr = label();
    if (cstr) write_cstring(cstr);
    else write_c("0");
    write_c(") {\n");
    write_c("  clear_flag(16);\n");
    write_c("  _%s();\n", trimclassname(name()));
    write_c("}\n\n");
    
    write_c("void %s::_%s() {\n", name(), trimclassname(name()));
//    write_c("  %s *w = this;\n", name());
  } else {
    write_h("public:\n");
    write_h("  %s(int X, int Y, int W, int H, const char *L = 0);\n", trimclassname(name()));

    write_c("%s::%s(int X, int Y, int W, int H, const char *L)\n", name(), trimclassname(name()));
    if (wc_relative)
      write_c("  : %s(0, 0, W, H, L) {\n", c);
    else
      write_c("  : %s(X, Y, W, H, L) {\n", c);
  }

//  write_c("  %s *o = this;\n", name());

  write_widget_code();
}

void Fl_Widget_Class_Type::write_code2() {
  write_extra_code();
  if (wc_relative) write_c("%sposition(X, Y);\n", indent());
  if (pIsModal) write_c("%sset_modal();\n", indent());
  else if (pIsNonModal) write_c("%sset_non_modal();\n", indent());
  if (!((fltk3::Window*)o)->border()) write_c("%sclear_border();\n", indent());
  if (xclass) {
    write_c("%sxclass(", indent());
    write_cstring(xclass);
    write_c(");\n");
  }
  write_c("%send();\n", indent());
  if (((fltk3::Window*)o)->resizable() == o)
    write_c("%sresizable(this);\n", indent());
  write_c("}\n");
}

////////////////////////////////////////////////////////////////
// live mode support

fltk3::Widget *Fl_Window_Type::enter_live_mode(int) {
  fltk3::Window *win = new fltk3::Window(o->x(), o->y(), o->w(), o->h());
  live_widget = win;
  if (live_widget) {
    copy_properties();
    Fl_Type *n;
    for (n = next; n && n->level > level; n = n->next) {
      if (n->level == level+1)
        n->enter_live_mode();
    }
    win->end();
  }
  return live_widget;
}

void Fl_Window_Type::leave_live_mode() {
}

/**
 * copy all properties from the edit widget to the live widget
 */
void Fl_Window_Type::copy_properties() {
  Fl_Widget_Type::copy_properties();
  /// \todo copy resizing constraints over
}


//
// End of "$Id$".
//
