//
// "$Id$"
//
// Forms emulation header file for the Fast Light Tool Kit (FLTK).
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
//

#ifndef __FORMS_H__
#define __FORMS_H__

#include <gnui/Window.h>
#include <gnui/run.h>
#include <gnui/draw.h>
#include <gnui/Color.h>
#include <gnui/Style.h>

typedef gnui::Widget GNUI_OBJECT;
typedef gnui::Window GNUI_FORM;

////////////////////////////////////////////////////////////////
// Random constants & symbols defined by forms.h file:

#ifndef NULL
#define NULL 0
#endif
#ifndef FALSE
#define FALSE 0
#define TRUE 1
#endif

#define GNUI_ON		1
#define GNUI_OK		1
#define GNUI_VALID	1
#define GNUI_PREEMPT	1
#define GNUI_AUTO		2
#define GNUI_WHEN_NEEDED	GNUI_AUTO
#define GNUI_OFF		0
#define GNUI_NONE		0
#define GNUI_CANCEL	0
#define GNUI_INVALID	0
#define GNUI_IGNORE	-1
#define GNUI_CLOSE	-2

#define GNUI_LCOL		gnui::BLACK
#define GNUI_COL1		gnui::GRAY75
#define GNUI_MCOL		gnui::GRAY85
#define GNUI_LEFT_BCOL	gnui::GRAY99
#define GNUI_TOP_BCOL	gnui::GRAY90
#define GNUI_BOTTOM_BCOL	gnui::GRAY35
#define GNUI_RIGHT_BCOL	gnui::GRAY20
#define GNUI_INACTIVE	gnui::GRAY66
#define GNUI_INACTIVE_COL	gnui::GRAY66
#define GNUI_FREE_COL1	gnui::Color(16)
#define GNUI_FREE_COL2	gnui::Color(17)
#define GNUI_FREE_COL3	gnui::Color(18)
#define GNUI_FREE_COL4	gnui::Color(19)
#define GNUI_FREE_COL5	gnui::Color(20)
#define GNUI_FREE_COL6	gnui::Color(21)
#define GNUI_FREE_COL7	gnui::Color(22)
#define GNUI_FREE_COL8	gnui::Color(23)
#define GNUI_FREE_COL9	gnui::Color(24)
#define GNUI_FREE_COL10	gnui::Color(25)
#define GNUI_FREE_COL11	gnui::Color(26)
#define GNUI_FREE_COL12	gnui::Color(27)
#define GNUI_FREE_COL13	gnui::Color(28)
#define GNUI_FREE_COL14	gnui::Color(29)
#define GNUI_FREE_COL15	gnui::Color(30)
#define GNUI_FREE_COL16	gnui::Color(31)
#define GNUI_TOMATO	gnui::Color(131)
#define GNUI_INDIANRED	gnui::Color(164)
#define GNUI_SLATEBLUE	gnui::Color(195)
#define GNUI_DARKGOLD	gnui::Color(84)
#define GNUI_PALEGREEN	gnui::Color(157)
#define GNUI_ORCHID	gnui::Color(203)
#define GNUI_DARKCYAN	gnui::Color(189)
#define GNUI_DARKTOMATO	gnui::Color(113)
#define GNUI_WHEAT	gnui::Color(174)

#define GNUI_ALIGN_BESIDE	gnui::ALIGN_INSIDE

#define GNUI_PUP_TOGGLE	2 // GNUI_MENU_TOGGLE
#define GNUI_PUP_INACTIVE 1 // GNUI_MENU_INACTIVE
#define GNUI_NO_FRAME	gnui::NO_BOX
#define GNUI_ROUNDED3D_UPBOX 	gnui::ROUND_UP_BOX
#define GNUI_ROUNDED3D_DOWNBOX	gnui::ROUND_DOWN_BOX
#define GNUI_OVAL3D_UPBOX		gnui::ROUND_UP_BOX
#define GNUI_OVAL3D_DOWNBOX	gnui::ROUND_DOWN_BOX

#define GNUI_MBUTTON1	1
#define GNUI_LEFTMOUSE	1
#define GNUI_MBUTTON2	2
#define GNUI_MIDDLEMOUSE	2
#define GNUI_MBUTTON3	3
#define GNUI_RIGHTMOUSE	3
#define GNUI_MBUTTON4	4
#define GNUI_MBUTTON5	5

#define GNUI_INVALID_STYLE 255
#define GNUI_NORMAL_STYLE	0
#define GNUI_BOLD_STYLE	1
#define GNUI_ITALIC_STYLE	2
#define GNUI_BOLDITALIC_STYLE 3
#define GNUI_FIXED_STYLE	4
#define GNUI_FIXEDBOLD_STYLE 5
#define GNUI_FIXEDITALIC_STYLE 6
#define GNUI_FIXEDBOLDITALIC_STYLE 7
#define GNUI_TIMES_STYLE	8
#define GNUI_TIMESBOLD_STYLE 9
#define GNUI_TIMESITALIC_STYLE 10
#define GNUI_TIMESBOLDITALIC_STYLE 11

// hacks to change the labeltype() when passed to gnui_set_object_lstyle():
#define GNUI_SHADOW_STYLE		0x100
#define GNUI_ENGRAVED_STYLE	0x200
#define GNUI_EMBOSSED_STYLE	0x300

// size values are different from XForms, match older Forms:
#define GNUI_TINY_SIZE	8
#define GNUI_SMALL_SIZE	11 // 10
#undef GNUI_NORMAL_SIZE
#define GNUI_NORMAL_SIZE	14 // 12
#define GNUI_MEDIUM_SIZE	18 // 14
#define GNUI_LARGE_SIZE	24 // 18
#define GNUI_HUGE_SIZE	32 // 24
#define GNUI_DEFAULT_SIZE	GNUI_SMALL_SIZE
#define GNUI_TINY_FONT	GNUI_TINY_SIZE
#define GNUI_SMALL_FONT	GNUI_SMALL_SIZE
#define GNUI_NORMAL_FONT	GNUI_NORMAL_SIZE
#define GNUI_MEDIUM_FONT	GNUI_MEDIUM_SIZE
#define GNUI_LARGE_FONT	GNUI_LARGE_SIZE
#define GNUI_HUGE_FONT	GNUI_HUGE_SIZE
#define GNUI_NORMAL_FONT1	GNUI_SMALL_FONT
#define GNUI_NORMAL_FONT2	GNUI_NORMAL_FONT
#define GNUI_DEFAULT_FONT	GNUI_SMALL_FONT

#define GNUI_RETURN_END_CHANGED	GNUI_WHEN_RELEASE
#define GNUI_RETURN_CHANGED	GNUI_WHEN_CHANGED
#define GNUI_RETURN_END		GNUI_WHEN_RELEASE_ALWAYS
#define GNUI_RETURN_ALWAYS	(GNUI_WHEN_CHANGED|GNUI_WHEN_NOT_CHANGED)

#define GNUI_BOUND_WIDTH	3

typedef int GNUI_Coord;
typedef int GNUI_COLOR;

////////////////////////////////////////////////////////////////
// gnui interaction:

#define GNUI_CMD_OPT void
extern GNUI_FORMS_API void gnui_initialize(int*, char*[], const char*, GNUI_CMD_OPT*, int);
inline void gnui_finish() {}

typedef void (*GNUI_IO_CALLBACK) (int, void*);
inline void gnui_add_io_callback(int fd, short w, GNUI_IO_CALLBACK cb, void* v) {
  Fl::add_fd(fd,w,cb,v);}
inline void gnui_remove_io_callback(int fd, short, GNUI_IO_CALLBACK) {
  Fl::remove_fd(fd);} // removes all the callbacks!

// type of callback is different and no "id" number is returned:
inline void gnui_add_timeout(long msec, void (*cb)(void*), void* v) {
  Fl::add_timeout(msec*.001, (GNUI_Timeout_Handler)cb, v);}
inline void gnui_remove_timeout(int) {}

// type of callback is different!
inline void gnui_set_idle_callback(void (*cb)()) {Fl::set_idle(cb);}

GNUI_FORMS_API GNUI_Widget* gnui_do_forms(void);
GNUI_FORMS_API GNUI_Widget* gnui_check_forms();
inline GNUI_Widget* gnui_do_only_forms(void) {return gnui_do_forms();}
inline GNUI_Widget* gnui_check_only_forms(void) {return gnui_check_forms();}

// because of new redraw behavior, these are no-ops:
inline void gnui_freeze_object(GNUI_Widget*) {}
inline void gnui_unfreeze_object(GNUI_Widget*) {}
inline void gnui_freeze_form(GNUI_Window*) {}
inline void gnui_unfreeze_form(GNUI_Window*) {}
inline void gnui_freeze_all_forms() {}
inline void gnui_unfreeze_all_forms() {}

inline void gnui_set_focus_object(GNUI_Window*, GNUI_Widget* o) {Fl::focus(o);}
inline void gnui_reset_focus_object(GNUI_Widget* o) {Fl::focus(o);}
#define gnui_set_object_focus gnui_set_focus_object

// void gnui_set_form_atclose(GNUI_Window*w,int (*cb)(GNUI_Window*,void*),void* v)
// void gnui_set_atclose(int (*cb)(GNUI_Window*,void*),void*)
// gnui_set_form_atactivate/atdeactivate not implemented!

////////////////////////////////////////////////////////////////
// GNUI_Widget:

inline void gnui_set_object_boxtype(GNUI_Widget* o, GNUI_Boxtype a) {o->box(a);}
inline void gnui_set_object_lsize(GNUI_Widget* o,int s) {o->label_size(s);}
GNUI_FORMS_API void gnui_set_object_lstyle(GNUI_Widget* o,int a);
inline void gnui_set_object_lcol(GNUI_Widget* o, unsigned a) {o->label_color((GNUI_Color)a);}
#define gnui_set_object_lcolor  gnui_set_object_lcol
inline void gnui_set_object_lalign(GNUI_Widget* o, GNUI_Align a) { o->clear_flag(GNUI_ALIGN_MASK); o->set_flag(a);}
#define gnui_set_object_align gnui_set_object_lalign
inline void gnui_set_object_color(GNUI_Widget* o,unsigned a,unsigned b) {o->color((GNUI_Color)a); o->selection_color((GNUI_Color)b);}
inline void gnui_set_object_label(GNUI_Widget* o, const char* a) {o->label(a); o->redraw();}
inline void gnui_set_object_position(GNUI_Widget*o,int x,int y) {o->position(x,y);}
inline void gnui_set_object_size(GNUI_Widget* o, int w, int h) {o->size(w,h);}
inline void gnui_set_object_geometry(GNUI_Widget* o,int x,int y,int w,int h) {o->resize(x,y,w,h);}

inline void gnui_get_object_geometry(GNUI_Widget* o,int*x,int*y,int*w,int*h) {
  *x = o->x(); *y = o->y(); *w = o->w(); *h = o->h();}
inline void gnui_get_object_position(GNUI_Widget* o,int*x,int*y) {
  *x = o->x(); *y = o->y();}

typedef void (*Forms_CB)(GNUI_Widget*, long);
inline void gnui_set_object_callback(GNUI_Widget*o,Forms_CB c,long a) {o->callback(c,a);}
#define gnui_set_call_back      gnui_set_object_callback
inline void gnui_call_object_callback(GNUI_Widget* o) {o->do_callback();}
inline void gnui_trigger_object(GNUI_Widget* o) {o->do_callback();}
inline void gnui_set_object_return(GNUI_Widget* o, int v) {
  o->when(v|GNUI_WHEN_RELEASE);}

inline void gnui_redraw_object(GNUI_Widget* o) {o->redraw();}
inline void gnui_show_object(GNUI_Widget* o) {o->show();}
inline void gnui_hide_object(GNUI_Widget* o) {o->hide();}
inline void gnui_free_object(GNUI_Widget* x) {delete x;}
inline void gnui_delete_object(GNUI_Widget* o) {((GNUI_Group*)(o->parent()))->remove(*o);}
inline void gnui_activate_object(GNUI_Widget* o) {o->activate();}
inline void gnui_deactivate_object(GNUI_Widget* o) {o->deactivate();}

inline void gnui_add_object(GNUI_Window* f, GNUI_Widget* x) {f->add(x);}
inline void gnui_insert_object(GNUI_Widget* o, GNUI_Widget* b) {
    ((GNUI_Group*)(b->parent()))->insert(*o,b);}

inline GNUI_Window* GNUI_ObjWin(GNUI_Widget* o) {return o->window();}

////////////////////////////////////////////////////////////////
// things that appered in the demos a lot that I don't emulate, but
// I did not want to edit out of all the demos...

inline int gnui_get_border_width() {return 3;}
inline void gnui_set_border_width(int) {}
inline void gnui_set_object_dblbuffer(GNUI_Widget*, int) {}
inline void gnui_set_form_dblbuffer(GNUI_Window*, int) {}

////////////////////////////////////////////////////////////////
// GNUI_Window:

inline void gnui_free_form(GNUI_Window* x) {delete x;}
inline void gnui_redraw_form(GNUI_Window* f) {f->redraw();}

inline GNUI_Window* gnui_bgn_form(GNUI_Boxtype b,int w,int h) {
  GNUI_Window* g = new GNUI_Window(w,h,0);
  g->box(b);
  return g;
}
inline void gnui_addto_form(GNUI_Window* f) {f->begin();}
inline GNUI_Group* gnui_bgn_group() {return new GNUI_Group(0,0,0,0,0);}
inline void gnui_addto_group(GNUI_Widget* o) {((GNUI_Group* )o)->begin();}
GNUI_FORMS_API void gnui_end_group();
GNUI_FORMS_API void gnui_end_form();
#define resizebox _ddfdesign_kludge()

inline void gnui_scale_form(GNUI_Window* f, double x, double y) {
  f->resizable(f); f->size(int(f->w()*x),int(f->h()*y));}
inline void gnui_set_form_position(GNUI_Window* f,int x,int y) {f->position(x,y);}
inline void gnui_set_form_size(GNUI_Window* f, int w, int h) {f->size(w,h);}
inline void gnui_set_form_geometry(GNUI_Window* f,int x,int y,int w,int h) {
  f->resize(x,y,w,h);}
#define gnui_set_initial_placement gnui_set_form_geometry
inline void gnui_adjust_form_size(GNUI_Window*) {}

GNUI_FORMS_API void gnui_show_form(GNUI_Window* f,int p,int b,const char* n);
enum {	// "p" argument values:
  GNUI_PLACE_FREE = 0,	// make resizable
  GNUI_PLACE_MOUSE = 1,	// mouse centered on form
  GNUI_PLACE_CENTER = 2,	// center of the screen
  GNUI_PLACE_POSITION = 4,// fixed position, resizable
  GNUI_PLACE_SIZE = 8,	// fixed size, normal gnui behavior
  GNUI_PLACE_GEOMETRY =16,// fixed size and position
  GNUI_PLACE_ASPECT = 32,	// keep aspect ratio (ignored)
  GNUI_PLACE_FULLSCREEN=64,// fill screen
  GNUI_PLACE_HOTSPOT = 128,// enables hotspot
  GNUI_PLACE_ICONIC = 256,// iconic (ignored)
  GNUI_FREE_SIZE=(1<<14),	// force resizable
  GNUI_FIX_SIZE =(1<<15)	// force off resizable
};
#define GNUI_PLACE_FREE_CENTER (GNUI_PLACE_CENTER|GNUI_FREE_SIZE)
#define GNUI_PLACE_CENTERFREE  (GNUI_PLACE_CENTER|GNUI_FREE_SIZE)
enum {	// "b" arguement values:
  GNUI_NOBORDER = 0,
  GNUI_FULLBORDER,
  GNUI_TRANSIENT
//GNUI_MODAL = (1<<8)	// not implemented yet in Forms
};
inline void gnui_set_form_hotspot(GNUI_Window* w,int x,int y) {w->hotspot(x,y);}
inline void gnui_set_form_hotobject(GNUI_Window* w, GNUI_Widget* o) {w->hotspot(o);}
extern GNUI_FORMS_API char gnui_flip;	// in forms.C
inline void gnui_flip_yorigin() {gnui_flip = 1;}

#define gnui_prepare_form_window gnui_show_form
inline void gnui_show_form_window(GNUI_Window*) {}

inline void gnui_raise_form(GNUI_Window* f) {f->show();}

inline void gnui_hide_form(GNUI_Window* f) {f->hide();}
inline void gnui_pop_form(GNUI_Window* f) {f->show();}

extern GNUI_FORMS_API char gnui_modal_next; // in forms.C
inline void gnui_activate_all_forms() {}
inline void gnui_deactivate_all_forms() {gnui_modal_next = 1;}
inline void gnui_deactivate_form(GNUI_Window*w) {w->deactivate();}
inline void gnui_activate_form(GNUI_Window*w) {w->activate();}

inline void gnui_set_form_title(GNUI_Window* f, const char* s) {f->label(s);}
inline void gnui_title_form(GNUI_Window* f, const char* s) {f->label(s);}

typedef void (*Forms_FormCB)(GNUI_Widget*);
inline void gnui_set_form_callback(GNUI_Window* f,Forms_FormCB c) {f->callback(c);}
#define gnui_set_form_call_back gnui_set_form_callback

inline void gnui_init() {}
inline void gnui_set_graphics_mode(int r, int /*d*/) {
  Fl::visual(r ? GNUI_RGB : GNUI_INDEX);
  // d should add GNUI_DOUBLE, but that always fails in gnui 2.0
}

inline int gnui_form_is_visible(GNUI_Window* f) {return f->visible();}

inline int gnui_mouse_button() {return Fl::event_button();}
#define gnui_mousebutton gnui_mouse_button

#define gnui_free       free
#define gnui_malloc     malloc
#define gnui_calloc     calloc
#define gnui_realloc    realloc

////////////////////////////////////////////////////////////////
// Drawing functions.  Only usable inside an GNUI_Free object?

#if 0
inline void gnui_drw_box(GNUI_Boxtype b,int x,int y,int w,int h,GNUI_Color bgc,int=3) {
    b->draw(x,y,w,h,bgc);}
inline void gnui_drw_frame(GNUI_Boxtype b,int x,int y,int w,int h,GNUI_Color bgc,int=3) {
    b->draw(x,y,w,h,bgc,GNUI_FRAME_ONLY);}
#endif

inline void gnui_drw_text(GNUI_Align align, int x, int y, int w, int h,
		  GNUI_Color fgcolor, int size, GNUI_Font style,
		  const char* s) {
  gnui_font(style,size);
  gnui_color(fgcolor);
  gnui_draw(s,x,y,w,h,align);
}

// this does not work except for CENTER...
inline void gnui_drw_text_beside(GNUI_Align align, int x, int y, int w, int h,
		  GNUI_Color fgcolor, int size, GNUI_Font style,
		  const char* s) {
  gnui_font(style,size);
  gnui_color(fgcolor);
  gnui_draw(s,x,y,w,h,align);
}

//inline void gnui_set_font_name(GNUI_Font n,const char* s) {gnui_set_font(n,s);}

inline void gnui_mapcolor(GNUI_Color c, uchar r, uchar g, uchar b) {
  gnui_set_color(c,gnui_rgb(r,g,b));}
#define gnui_set_clipping(x,y,w,h) gnui_clip(x,y,w,h)
#define gnui_unset_clipping() gnui_pop_clip()

////////////////////////////////////////////////////////////////
// Forms classes:

inline GNUI_Widget* gnui_add_new(GNUI_Widget* p) {return p;}
inline GNUI_Widget* gnui_add_new(uchar t,GNUI_Widget* p) {p->type(t); return p;}

#define forms_constructor(type,name) \
inline type* name(uchar t,int x,int y,int w,int h,const char* l) { \
 return (type*)(gnui_add_new(t, new type(x,y,w,h,l)));}
#define forms_constructort(type,name) \
inline type* name(uchar t,int x,int y,int w,int h,const char* l) { \
 return (type*)(gnui_add_new(new type(t,x,y,w,h,l)));}
#define forms_constructorb(type,name) \
inline type* name(GNUI_Boxtype t,int x,int y,int w,int h,const char* l) { \
 return (type*)(gnui_add_new(new type(t,x,y,w,h,l)));}

#include "GNUI_FormsBitmap.h"
#define GNUI_NORMAL_BITMAP GNUI_NO_BOX
forms_constructorb(GNUI_FormsBitmap, gnui_add_bitmap)
inline void gnui_set_bitmap_data(GNUI_Widget* o, int w, int h, const uchar* b) {
    ((GNUI_FormsBitmap*)o)->set(w,h,b);
}

#include "GNUI_FormsPixmap.h"
#define GNUI_NORMAL_PIXMAP GNUI_NO_BOX
forms_constructorb(GNUI_FormsPixmap, gnui_add_pixmap)
inline void gnui_set_pixmap_data(GNUI_Widget* o, char*const* b) {
    ((GNUI_FormsPixmap*)o)->set(b);
}
//inline void gnui_set_pixmap_file(GNUI_Widget*, const char*);
inline void gnui_set_pixmap_align(GNUI_Widget* o,GNUI_Align a,int,int) { o->clear_flag(GNUI_ALIGN_MASK); o->set_flag(a);}
//inline void gnui_set_pixmap_colorcloseness(int, int, int);

#include <gnui/GNUI_Box.h>
forms_constructorb(GNUI_Box, gnui_add_box)

#include <gnui/GNUI_Browser.h>
forms_constructor(GNUI_Browser, gnui_add_browser)

inline void gnui_clear_browser(GNUI_Widget* o) {
    ((GNUI_Browser*)o)->clear();}
inline void gnui_add_browser_line(GNUI_Widget* o, const char* s) {
    ((GNUI_Browser*)o)->add(s);}
inline void gnui_addto_browser(GNUI_Widget* o, const char* s) {
    ((GNUI_Browser*)o)->add(s);} /* should also scroll to bottom */
//inline void gnui_addto_browser_chars(GNUI_Widget*, const char*)
//#define gnui_append_browser gnui_addto_browser_chars
inline void gnui_insert_browser_line(GNUI_Widget* o, int n, const char* s) {
    ((GNUI_Browser*)o)->insert(n,s);}
inline void gnui_delete_browser_line(GNUI_Widget* o, int n) {
    ((GNUI_Browser*)o)->remove(n);}
inline void gnui_replace_browser_line(GNUI_Widget* o, int n, const char* s) {
    ((GNUI_Browser*)o)->replace(n,s);}
inline char* gnui_get_browser_line(GNUI_Widget* o, int n) {
    return (char*)(((GNUI_Browser*)o)->text(n));}
GNUI_FORMS_API int gnui_load_browser(GNUI_Widget* o, const char* f);
inline void gnui_select_browser_line(GNUI_Widget* o, int n) {
    ((GNUI_Browser*)o)->select(n,1);}
inline void gnui_deselect_browser_line(GNUI_Widget* o, int n) {
    ((GNUI_Browser*)o)->select(n,0);}
inline void gnui_deselect_browser(GNUI_Widget* o) {
    ((GNUI_Browser*)o)->deselect();}
inline int gnui_isselected_browser_line(GNUI_Widget* o, int n) {
    return ((GNUI_Browser*)o)->selected(n);}
inline int gnui_get_browser_topline(GNUI_Widget* o) {
    return ((GNUI_Browser*)o)->topline();}
inline int gnui_get_browser(GNUI_Widget* o) {
    return ((GNUI_Browser*)o)->value();}
inline int gnui_get_browser_maxline(GNUI_Widget* o) {
    return ((GNUI_Browser*)o)->size();}
//linline int gnui_get_browser_screenlines(GNUI_Widget*);
inline void gnui_set_browser_topline(GNUI_Widget* o, int n) {
    ((GNUI_Browser*)o)->topline(n);}
inline void gnui_set_browser_fontsize(GNUI_Widget* o, int s) {
    ((GNUI_Browser*)o)->text_size(s);}
inline void gnui_set_browser_fontstyle(GNUI_Widget* o, int s) {
    ((GNUI_Browser*)o)->text_font(gnui_fonts+s);}
inline void gnui_set_browser_specialkey(GNUI_Widget* o, char c) {
    ((GNUI_Browser*)o)->format_char(c);}
//inline void gnui_set_browser_vscrollbar(GNUI_Widget*, int);
//inline void gnui_set_browser_hscrollbar(GNUI_Widget*, int);
//inline void gnui_set_browser_leftslider(GNUI_Widget*, int);
//#define gnui_set_browser_leftscrollbar gnui_set_browser_leftslider
//inline void gnui_set_browser_line_selectable(GNUI_Widget*, int, int);
//inline void gnui_get_browser_dimension(GNUI_Widget*,int*,int*,int*,int*);
//inline void gnui_set_browser_dblclick_callback(GNUI_Widget*,GNUI_CALLBACKPTR,long);
//inline void gnui_set_browser_xoffset(GNUI_Widget*, GNUI_Coord);
//inline void gnui_set_browser_scrollbarsize(GNUI_Widget*, int, int);
inline void gnui_setdisplayed_browser_line(GNUI_Widget* o, int n, int i) {
    ((GNUI_Browser*)o)->display(n,i);}
inline int gnui_isdisplayed_browser_line(GNUI_Widget* o, int n) {
    return ((GNUI_Browser*)o)->displayed(n);}

#include <gnui/GNUI_Button.h>

#define GNUI_NORMAL_BUTTON	0
//#define GNUI_HIDDEN_BUTTON
#define GNUI_TOUCH_BUTTON		4
#define GNUI_INOUT_BUTTON		5
#define GNUI_RETURN_BUTTON	6
#define GNUI_HIDDEN_RET_BUTTON	7
#define GNUI_PUSH_BUTTON		GNUI_TOGGLE_BUTTON
#define GNUI_MENU_BUTTON		9

extern GNUI_FORMS_API int gnui_old_shortcut(const char*);

GNUI_FORMS_API GNUI_Button* gnui_add_button(uchar t,int x,int y,int w,int h,const char* l);
inline int gnui_get_button(GNUI_Widget* b) {return ((GNUI_Button*)b)->value();}
inline void gnui_set_button(GNUI_Widget* b, int v) {((GNUI_Button*)b)->value(v);}
inline int gnui_get_button_numb(GNUI_Widget*) {return Fl::event_button();}
inline void gnui_set_object_shortcut(GNUI_Widget* b, const char* s, int=0) {
  b->shortcut(gnui_old_shortcut(s));}
#define gnui_set_button_shortcut gnui_set_object_shortcut

#include <gnui/GNUI_Light_Button.h>
forms_constructor(GNUI_Light_Button, gnui_add_lightbutton)

#include <gnui/GNUI_Round_Button.h>
forms_constructor(GNUI_Round_Button, gnui_add_roundbutton)
forms_constructor(GNUI_Round_Button, gnui_add_round3dbutton)

#include <gnui/GNUI_Check_Button.h>
forms_constructor(GNUI_Check_Button, gnui_add_checkbutton)

inline GNUI_Widget* gnui_add_bitmapbutton(int t,int x,int y,int w,int h,const char* l) {GNUI_Widget* o = gnui_add_button(t,x,y,w,h,l); return o;}
inline void gnui_set_bitmapbutton_data(GNUI_Widget* o,int a,int b,uchar* c) {
  (new GNUI_Bitmap(c,a,b))->label(o);}  // does not delete old GNUI_Bitmap!

inline GNUI_Widget* gnui_add_pixmapbutton(int t,int x,int y,int w,int h,const char* l) {GNUI_Widget* o = gnui_add_button(t,x,y,w,h,l); return o;}
inline void gnui_set_pixmapbutton_data(GNUI_Widget* o, const char*const* c) {
  (new GNUI_Pixmap(c))->label(o);}  // does not delete old GNUI_Pixmap!

// GNUI_Canvas object not yet implemented!

#include "GNUI_Chart.h"

forms_constructor(GNUI_Chart, gnui_add_chart)
inline void gnui_clear_chart(GNUI_Widget* o) {
  ((GNUI_Chart*)o)->clear();}
inline void gnui_add_chart_value(GNUI_Widget* o,double v,const char* s,uchar c){
  ((GNUI_Chart*)o)->add(v,s,c);}
inline void gnui_insert_chart_value(GNUI_Widget* o, int i, double v, const char* s, uchar c) {
  ((GNUI_Chart*)o)->insert(i,v,s,c);}
inline void gnui_replace_chart_value(GNUI_Widget* o, int i, double v, const char* s, uchar c) {
  ((GNUI_Chart*)o)->replace(i,v,s,c);}
inline void gnui_set_chart_bounds(GNUI_Widget* o, double a, double b) {
  ((GNUI_Chart*)o)->bounds(a,b);}
inline void gnui_set_chart_maxnumb(GNUI_Widget* o, int v) {
  ((GNUI_Chart*)o)->maxsize(v);}
inline void gnui_set_chart_autosize(GNUI_Widget* o, int v) {
  ((GNUI_Chart*)o)->autosize(v);}
inline void gnui_set_chart_lstyle(GNUI_Widget* o, GNUI_Font v) {
  ((GNUI_Chart*)o)->text_font(v);}
inline void gnui_set_chart_lsize(GNUI_Widget* o, int v) {
  ((GNUI_Chart*)o)->text_size(v);}
inline void gnui_set_chart_lcolor(GNUI_Widget* o, unsigned v) {
  ((GNUI_Chart*)o)->text_color((GNUI_Color)v);}
#define gnui_set_chart_lcol   gnui_set_chart_lcolor

#include <gnui/GNUI_Choice.h>

#define GNUI_NORMAL_CHOICE	0
#define GNUI_NORMAL_CHOICE2	0
#define GNUI_DROPLIST_CHOICE	0

forms_constructor(GNUI_Choice, gnui_add_choice)
inline void gnui_clear_choice(GNUI_Widget* o) {
    ((GNUI_Choice*)o)->clear();}
inline void gnui_addto_choice(GNUI_Widget* o, const char* s) {
    ((GNUI_Choice*)o)->add(s);}
inline void gnui_replace_choice(GNUI_Widget* o, int i, const char* s) {
    ((GNUI_Choice*)o)->replace(i-1,s);}
inline void gnui_delete_choice(GNUI_Widget* o, int i) {
    ((GNUI_Choice*)o)->remove(i-1);}
inline void gnui_set_choice(GNUI_Widget* o, int i) {
    ((GNUI_Choice*)o)->value(i-1);}
// inline void gnui_set_choice_text(GNUI_Widget*, const char*);
inline int gnui_get_choice(GNUI_Widget* o) {
    return ((GNUI_Choice*)o)->value()+1;}
// inline const char* gnui_get_choice_item_text(GNUI_Widget*, int);
// inline int gnui_get_choice_maxitems(GNUI_Widget*);
inline const char* gnui_get_choice_text(GNUI_Widget* o) {
    return ((GNUI_Choice*)o)->text();}
inline void gnui_set_choice_fontsize(GNUI_Widget* o, int x) {
    ((GNUI_Choice*)o)->text_size(x);}
inline void gnui_set_choice_fontstyle(GNUI_Widget* o, GNUI_Font x) {
    ((GNUI_Choice*)o)->text_font(x);}
// inline void gnui_set_choice_item_mode(GNUI_Widget*, int, unsigned);
// inline void gnui_set_choice_item_shortcut(GNUI_Widget*, int, const char*);

#include <gnui/GNUI_Clock.h>
forms_constructor(GNUI_Clock, gnui_add_clock)
inline void gnui_get_clock(GNUI_Widget* o, int* h, int* m, int* s) {
    *h = ((GNUI_Clock*)o)->hour();
    *m = ((GNUI_Clock*)o)->minute();
    *s = ((GNUI_Clock*)o)->second();
}

#include <gnui/GNUI_Counter.h>
forms_constructor(GNUI_Counter, gnui_add_counter)
inline void gnui_set_counter_value(GNUI_Widget* o, double v) {
    ((GNUI_Counter*)o)->value(v);}
inline void gnui_set_counter_bounds(GNUI_Widget* o, double a, double b) {
    ((GNUI_Counter*)o)->range(a,b);}
inline void gnui_set_counter_step(GNUI_Widget* o, double a, double b) {
    ((GNUI_Counter*)o)->step(a / b);}
inline void gnui_set_counter_precision(GNUI_Widget* o, int v) {
//    ((GNUI_Counter*)o)->precision(v);}
    ((GNUI_Counter*)o)->step(1/(10^v));}
inline void gnui_set_counter_return(GNUI_Widget* o, int v) {
    ((GNUI_Counter*)o)->when(v|GNUI_WHEN_RELEASE);}
inline double gnui_get_counter_value(GNUI_Widget* o) {
    return ((GNUI_Counter*)o)->value();}
inline void gnui_get_counter_bounds(GNUI_Widget* o, float* a, float* b) {
  *a = float(((GNUI_Counter*)o)->minimum());
  *b = float(((GNUI_Counter*)o)->maximum());
}
//inline void gnui_set_counter_filter(GNUI_Widget*,const char* (*)(GNUI_Widget*,double,int));

// Cursor stuff cannot be emulated because it uses X stuff
inline void gnui_set_cursor(GNUI_Window* w, GNUI_Cursor c) {w->cursor(c);}
#define GNUI_INVISIBLE_CURSOR GNUI_CURSOR_NONE
#define GNUI_DEFAULT_CURSOR GNUI_CURSOR_DEFAULT

#include <gnui/GNUI_Dial.h>

#define GNUI_DIAL_COL1 GNUI_GRAY
#define GNUI_DIAL_COL2 37

forms_constructor(GNUI_Dial, gnui_add_dial)
inline void gnui_set_dial_value(GNUI_Widget* o, double v) {
  ((GNUI_Dial*)o)->value(v);}
inline double gnui_get_dial_value(GNUI_Widget* o) {
  return ((GNUI_Dial*)o)->value();}
inline void gnui_set_dial_bounds(GNUI_Widget* o, double a, double b) {
  ((GNUI_Dial*)o)->range(a, b);}
inline void gnui_get_dial_bounds(GNUI_Widget* o, float* a, float* b) {
  *a = float(((GNUI_Dial*)o)->minimum());
  *b = float(((GNUI_Dial*)o)->maximum());
}
inline void gnui_set_dial_return(GNUI_Widget* o, int i) {
  ((GNUI_Dial*)o)->when(i|GNUI_WHEN_RELEASE);}
inline void gnui_set_dial_angles(GNUI_Widget* o, int a, int b) {
  ((GNUI_Dial*)o)->angles(a, b);}
//inline void gnui_set_dial_cross(GNUI_Widget* o, int);
// inline void gnui_set_dial_direction(GNUI_Widget* o, uchar d) {
//   ((GNUI_Dial*)o)->direction(d);}
inline void gnui_set_dial_step(GNUI_Widget* o, double v) {
  ((GNUI_Dial*)o)->step(v);}

// Frames:

inline GNUI_Widget* gnui_add_frame(GNUI_Boxtype i,int x,int y,int w,int h,const char* l) {
  return gnui_add_box(i,x-3,y-3,w+6,h+6,l);}

// labelframe nyi
inline GNUI_Widget* gnui_add_labelframe(GNUI_Boxtype i,int x,int y,int w,int h,const char* l) {
  GNUI_Widget* o = gnui_add_box(i,x-3,y-3,w+6,h+6,l);
  o->clear_flag(GNUI_ALIGN_MASK); 
  o->set_flag(GNUI_ALIGN_TOP | GNUI_ALIGN_LEFT);
  return o;
}

#include "GNUI_Free.h"
inline GNUI_Free*
gnui_add_free(int t,double x,double y,double w,double h,const char* l,
	    GNUI_HANDLEPTR hdl) {
 return (GNUI_Free*)(gnui_add_new(
   new GNUI_Free(t,int(x),int(y),int(w),int(h),l,hdl)));
}

#include <gnui/gnui_ask.h>
#include <gnui/gnui_show_colormap.h>

inline int gnui_show_question(const char* c, int = 0) {return gnui_ask(c);}
GNUI_FORMS_API void gnui_show_message(const char *,const char *,const char *);
GNUI_FORMS_API void gnui_show_alert(const char *,const char *,const char *,int=0);
GNUI_FORMS_API int gnui_show_question(const char *,const char *,const char *);
inline const char *gnui_show_input(const char *l,const char*d=0) {return gnui_input(l,d);}
/*const*/ char *gnui_show_simple_input(const char *label, const char *deflt = 0);
int gnui_show_choice(
    const char *m1,
    const char *m2,
    const char *m3,
    int numb,
    const char *b0,
    const char *b1,
    const char *b2);

inline void gnui_set_goodies_font(int a, unsigned b) {
  gnui_message_style->label_font = gnui_fonts+a;
  gnui_message_style->label_size = b;
}
#define gnui_show_messages gnui_message
inline int gnui_show_choices(const char* c,int n,const char* b1,const char* b2,
			   const char* b3, int) {
  return gnui_show_choice(0,c,0,n,b1,b2,b3);
}

#include <gnui/filename.h>
#include <gnui/gnui_file_chooser.h>
inline int do_matching(char* a, const char* b) {return filename_match(a,b);}

// Forms-compatable file chooser (implementation in fselect.C):
GNUI_FORMS_API char* gnui_show_file_selector(const char* message,const char* dir,
			    const char* pat,const char* fname);
GNUI_FORMS_API char*	gnui_get_directory();
GNUI_FORMS_API char*	gnui_get_pattern();
GNUI_FORMS_API char*	gnui_get_filename();

#include <gnui/GNUI_Input.h>
forms_constructor(GNUI_Input, gnui_add_input)
inline void gnui_set_input(GNUI_Widget* o, const char* v) {
    ((GNUI_Input*)o)->value(v);}
inline void gnui_set_input_return(GNUI_Widget* o, int x) {
    ((GNUI_Input*)o)->when(x | GNUI_WHEN_RELEASE);}
inline void gnui_set_input_color(GNUI_Widget* o, unsigned a, unsigned /*b*/) {
    ((GNUI_Input*)o)->text_color((GNUI_Color)a);
//  ((GNUI_Input*)o)->cursor_color((GNUI_Color)b);
}
// inline void gnui_set_input_scroll(GNUI_Widget*, int);
inline void gnui_set_input_cursorpos(GNUI_Widget* o, int x, int /*y*/) {
  ((GNUI_Input*)o)->position(x);}
// inline void gnui_set_input_selected(GNUI_Widget*, int);
// inline void gnui_set_input_selected_range(GNUI_Widget*, int, int);
// inline void gnui_set_input_maxchars(GNUI_Widget*, int);
// inline void gnui_set_input_format(GNUI_Widget*, int, int);
// inline void gnui_set_input_hscrollbar(GNUI_Widget*, int);
// inline void gnui_set_input_vscrollbar(GNUI_Widget*, int);
// inline void gnui_set_input_xoffset(GNUI_Widget*, int);
// inline void gnui_set_input_topline(GNUI_Widget*, int);
// inline void gnui_set_input_scrollbarsize(GNUI_Widget*, int, int);
// inline int gnui_get_input_topline(GNUI_Widget*);
// inline int gnui_get_input_screenlines(GNUI_Widget*);
inline int gnui_get_input_cursorpos(GNUI_Widget* o, int*x, int*y) {
  *x = ((GNUI_Input*)o)->position(); *y = 0; return *x;}
// inline int gnui_get_input_numberoflines(GNUI_Widget*);
// inline void gnui_get_input_format(GNUI_Widget*, int*, int*);
inline const char* gnui_get_input(GNUI_Widget* o) {return ((GNUI_Input*)o)->value();}

#include <gnui/GNUI_Menu_Button.h>

// types are not implemented, they all act like GNUI_PUSH_MENU:
#define GNUI_TOUCH_MENU		0
#define GNUI_PUSH_MENU		1
#define GNUI_PULLDOWN_MENU	2
forms_constructor(GNUI_Menu_Button, gnui_add_menu)

inline void gnui_clear_menu(GNUI_Widget* o) {
    ((GNUI_Menu_Button*)o)->clear();}
inline void gnui_set_menu(GNUI_Widget* o, const char* s) {
    ((GNUI_Menu_Button*)o)->clear(); ((GNUI_Menu_Button*)o)->add(s);}
inline void gnui_addto_menu(GNUI_Widget* o, const char* s) {
    ((GNUI_Menu_Button*)o)->add(s);}
inline void gnui_replace_menu_item(GNUI_Widget* o, int i, const char* s) {
    ((GNUI_Menu_Button*)o)->replace(i-1,s);}
inline void gnui_delete_menu_item(GNUI_Widget* o, int i) {
    ((GNUI_Menu_Button*)o)->remove(i-1);}
inline void gnui_set_menu_item_shortcut(GNUI_Widget* o, int i, const char* s) {
    ((GNUI_Menu_Button*)o)->shortcut(i-1,gnui_old_shortcut(s));}
// inline void gnui_set_menu_item_mode(GNUI_Widget* o, int i, long x) {
//     ((GNUI_Menu_Button*)o)->mode(i-1,x);}
inline void gnui_show_menu_symbol(GNUI_Widget*, int ) {
/*    ((GNUI_Menu_Button*)o)->show_menu_symbol(i); */}
// inline void gnui_set_menu_popup(GNUI_Widget*, int);
inline int gnui_get_menu(GNUI_Widget* o) {
    return ((GNUI_Menu_Button*)o)->value()+1;}
inline const char* gnui_get_menu_item_text(GNUI_Widget* o, int i) {
    return ((GNUI_Menu_Button*)o)->text(i);}
inline int gnui_get_menu_maxitems(GNUI_Widget* o) {
    return ((GNUI_Menu_Button*)o)->size();}
inline int gnui_get_menu_item_mode(GNUI_Widget* o, int i) {
    return ((GNUI_Menu_Button*)o)->mode(i);}
inline const char* gnui_get_menu_text(GNUI_Widget* o) {
    return ((GNUI_Menu_Button*)o)->text();}

#include "GNUI_Positioner.h"
#define GNUI_NORMAL_POSITIONER	0
forms_constructor(GNUI_Positioner, gnui_add_positioner)
inline void gnui_set_positioner_xvalue(GNUI_Widget* o, double v) {
    ((GNUI_Positioner*)o)->xvalue(v);}
inline double gnui_get_positioner_xvalue(GNUI_Widget* o) {
    return ((GNUI_Positioner*)o)->xvalue();}
inline void gnui_set_positioner_xbounds(GNUI_Widget* o, double a, double b) {
    ((GNUI_Positioner*)o)->xbounds(a,b);}
inline void gnui_get_positioner_xbounds(GNUI_Widget* o, float* a, float* b) {
  *a = float(((GNUI_Positioner*)o)->xminimum());
  *b = float(((GNUI_Positioner*)o)->xmaximum());
}
inline void gnui_set_positioner_yvalue(GNUI_Widget* o, double v) {
    ((GNUI_Positioner*)o)->yvalue(v);}
inline double gnui_get_positioner_yvalue(GNUI_Widget* o) {
    return ((GNUI_Positioner*)o)->yvalue();}
inline void gnui_set_positioner_ybounds(GNUI_Widget* o, double a, double b) {
    ((GNUI_Positioner*)o)->ybounds(a,b);}
inline void gnui_get_positioner_ybounds(GNUI_Widget* o, float* a, float* b) {
  *a = float(((GNUI_Positioner*)o)->yminimum());
  *b = float(((GNUI_Positioner*)o)->ymaximum());
}
inline void gnui_set_positioner_xstep(GNUI_Widget* o, double v) {
    ((GNUI_Positioner*)o)->xstep(v);}
inline void gnui_set_positioner_ystep(GNUI_Widget* o, double v) {
    ((GNUI_Positioner*)o)->ystep(v);}
inline void gnui_set_positioner_return(GNUI_Widget* o, int v) {
    ((GNUI_Positioner*)o)->when(v|GNUI_WHEN_RELEASE);}

#include <gnui/GNUI_Slider.h>

#define GNUI_HOR_BROWSER_SLIDER GNUI_HOR_SLIDER
#define GNUI_VERT_BROWSER_SLIDER GNUI_VERT_SLIDER

forms_constructor(GNUI_Slider, gnui_add_slider)
#define GNUI_SLIDER_COL1 GNUI_GRAY
inline void gnui_set_slider_value(GNUI_Widget* o, double v) {
    ((GNUI_Slider*)o)->value(v);}
inline double gnui_get_slider_value(GNUI_Widget* o) {
    return ((GNUI_Slider*)o)->value();}
inline void gnui_set_slider_bounds(GNUI_Widget* o, double a, double b) {
    ((GNUI_Slider*)o)->range(a, b);}
inline void gnui_get_slider_bounds(GNUI_Widget* o, float* a, float* b) {
  *a = float(((GNUI_Slider*)o)->minimum());
  *b = float(((GNUI_Slider*)o)->maximum());
}
inline void gnui_set_slider_return(GNUI_Widget* o, int i) {
    ((GNUI_Slider*)o)->when(i|GNUI_WHEN_RELEASE);}
inline void gnui_set_slider_step(GNUI_Widget* o, double v) {
    ((GNUI_Slider*)o)->step(v);}
// inline void gnui_set_slider_increment(GNUI_Widget* o, double v, double);
inline void gnui_set_slider_size(GNUI_Widget* o, double v) {
    ((GNUI_Slider*)o)->slider_size(v);}

#include <gnui/GNUI_Value_Slider.h>
forms_constructor(GNUI_Value_Slider, gnui_add_valslider)

inline void gnui_set_slider_precision(GNUI_Widget* o, int i) {
  double v = 1.0;
  while (i--) v /= 10.0;
  ((GNUI_Value_Slider*)o)->step(v);
}

// The forms text object was the same as an GNUI_Box except it inverted the
// meaning of GNUI_ALIGN_INSIDE.  Implementation in forms.C
class GNUI_FORMS_API GNUI_FormsText : public GNUI_Widget {
protected:
    void draw();
public:
    GNUI_FormsText(GNUI_Boxtype b, int x, int y, int w, int h, const char* l=0)
	: GNUI_Widget(x,y,w,h,l) {box(b); clear_flag(GNUI_ALIGN_MASK); set_flag(GNUI_ALIGN_LEFT);}
};
#define GNUI_NORMAL_TEXT GNUI_NO_BOX
forms_constructorb(GNUI_FormsText, gnui_add_text)

#include "GNUI_Timer.h"
forms_constructort(GNUI_Timer, gnui_add_timer)
inline void gnui_set_timer(GNUI_Widget* o, double v) {((GNUI_Timer*)o)->value(v);}
inline double gnui_get_timer(GNUI_Widget* o) {return ((GNUI_Timer*)o)->value();}
inline void gnui_suspend_timer(GNUI_Widget* o) {((GNUI_Timer*)o)->suspended(1);}
inline void gnui_resume_timer(GNUI_Widget* o) {((GNUI_Timer*)o)->suspended(0);}
inline void gnui_set_timer_countup(GNUI_Widget* o,char d) {((GNUI_Timer*)o)->direction(d);}
GNUI_FORMS_API void gnui_gettime(long* sec, long* usec);

// GNUI_XYPlot nyi


// stuff from DDForms:

inline int gnui_double_click() {return Fl::event_clicks();}
inline void gnui_draw() {Fl::flush();}

#endif	/* define __FORMS_H__ */

//
// End of "$Id$".
//
