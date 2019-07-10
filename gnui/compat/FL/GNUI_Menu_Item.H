//
// "$Id$"
//
// Back-compatability menu items for FLTK.  The new gnui::Menu class
// converts these tables into child gnui::Item and gnui::ItemGroup widgets.
// You should not use this for new programs.
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

#ifndef GNUI_Menu_Item_h
#define GNUI_Menu_Item_h

#include <gnui/Widget.h>

enum { // values for flags:
  GNUI_MENU_INACTIVE = 1,
  GNUI_MENU_TOGGLE= 2,
  GNUI_MENU_VALUE = 4,
  GNUI_MENU_RADIO = 8,
  GNUI_MENU_INVISIBLE = 0x10,
  GNUI_SUBMENU_POINTER = 0x20,
  GNUI_SUBMENU = 0x40,
  GNUI_MENU_DIVIDER = 0x80,
  GNUI_MENU_HORIZONTAL = 0x100 // not used!
};

namespace gnui {
  class GNUI_API Menu;
}

struct GNUI_API GNUI_Menu_Item {
  const char *text;
  int shortcut_;
  gnui::Callback *callback_;
  void *user_data_;
  int flags;
  gnui::LabelType* labeltype_;
  gnui::Font* labelfont_;
  unsigned labelsize_;
  gnui::Color labelcolor_;

  // Used to add or set an gnui::Menu widget:
  void add_to(gnui::Menu*, void* data = 0) const;

  // popup menus without using an gnui::Menu widget:
  // Warning: this is now quite expensive, as it creates a temporary
  // gnui::Menu and child widgets!  These also do not match the gnui 1.0
  // calls, if there is any callback it is called directly (with the
  // dummy gnui::Menu as an argument).
  const GNUI_Menu_Item*
	pulldown(int X, int Y, int W, int H,
		 const GNUI_Menu_Item* picked = 0,
		 const char* title = 0) const;
  const GNUI_Menu_Item*
	popup(int X, int Y, const char* title=0,
	      const GNUI_Menu_Item* picked = 0) const {
    return pulldown(X, Y, 0, 0, picked, title);}
  const GNUI_Menu_Item*
	test_shortcut() const;

  // return offset of terminating null item:
  int size() const ;

  // advance a pointer by N items, skipping submenus:
  const GNUI_Menu_Item *next(int=1) const;
  GNUI_Menu_Item *next(int i=1) {
    return (GNUI_Menu_Item*)(((const GNUI_Menu_Item*)this)->next(i));}

  const char* label() const {return text;}
  gnui::LabelType* labeltype() const {return labeltype_;}
  gnui::Color labelcolor() const {return labelcolor_;}
  gnui::Font* labelfont() const {return labelfont_;}
  unsigned labelsize() const {return labelsize_;}
  gnui::Callback_p callback() const {return callback_;}
  void* user_data() const {return user_data_;}
  long argument() const {return (long)user_data_;}
  int shortcut() const {return shortcut_;}
  int submenu() const {return flags&(GNUI_SUBMENU|GNUI_SUBMENU_POINTER);}
  int checkbox() const {return flags&GNUI_MENU_TOGGLE;}
  int radio() const {return flags&GNUI_MENU_RADIO;}
  int value() const {return flags&GNUI_MENU_VALUE;}
  int visible() const {return !(flags&GNUI_MENU_INVISIBLE);}
  int active() const {return !(flags&GNUI_MENU_INACTIVE);}
  int activevisible() const {return !(flags&0x11);}

  void label(const char* a) {text=a;}
  void label(gnui::LabelType* a,const char* b) {labeltype_ = a; text = b;}
  void labeltype(gnui::LabelType* a) {labeltype_ = a;}
  void labelcolor(uchar a) {labelcolor_ = a;}
  void labelfont(gnui::Font* a) {labelfont_ = a;}
  void labelsize(uchar a) {labelsize_ = a;}
  void callback(gnui::Callback* c, void* p) {callback_=c; user_data_=p;}
  void callback(gnui::Callback* c) {callback_=c;}
  void callback(gnui::Callback0*c) {callback_=(gnui::Callback*)c;}
  void callback(gnui::Callback1*c, long p=0) {callback_=(gnui::Callback*)c; user_data_=(void*)p;}
  void user_data(void* v) {user_data_ = v;}
  void argument(long v) {user_data_ = (void*)v;}
  void shortcut(int s) {shortcut_ = s;}
  void set() {flags |= GNUI_MENU_VALUE;}
  void clear() {flags &= ~GNUI_MENU_VALUE;}
  void setonly();
  void show() {flags &= ~GNUI_MENU_INVISIBLE;}
  void hide() {flags |= GNUI_MENU_INVISIBLE;}
  void activate() {flags &= ~GNUI_MENU_INACTIVE;}
  void deactivate() {flags |= GNUI_MENU_INACTIVE;}

  const GNUI_Menu_Item* find_shortcut(int *ip=0) const;

  void do_callback(gnui::Widget* o) const {callback_(o, user_data_);}
  void do_callback(gnui::Widget* o,void* arg) const {callback_(o, arg);}
  void do_callback(gnui::Widget* o,long arg) const {callback_(o, (void*)arg);}

  // back-compatability, do not use:
  int checked() const {return flags&GNUI_MENU_VALUE;}
  void check() {flags |= GNUI_MENU_VALUE;}
  void uncheck() {flags &= ~GNUI_MENU_VALUE;}

#if 0
  int add(const char*, int shortcut, gnui::Callback*, void* =0, int = 0);
  int add(const char*a, const char* b, gnui::Callback* c,
	  void* d = 0, int e = 0) {
    return add(a,gnui::old_shortcut(b),c,d,e);}
#endif
};

typedef GNUI_Menu_Item GNUI_Menu; // back compatability with gnui < 1.0

enum {	// back-compatability enum:
  GNUI_PUP_NONE	= 0,
  GNUI_PUP_GREY	= GNUI_MENU_INACTIVE,
  GNUI_PUP_GRAY	= GNUI_MENU_INACTIVE,
  GNUI_MENU_BOX	= GNUI_MENU_TOGGLE,
  GNUI_PUP_BOX	= GNUI_MENU_TOGGLE,
  GNUI_MENU_CHECK	= GNUI_MENU_VALUE,
  GNUI_PUP_CHECK	= GNUI_MENU_VALUE,
  GNUI_PUP_RADIO	= GNUI_MENU_RADIO,
  GNUI_PUP_INVISIBLE = GNUI_MENU_INVISIBLE,
  GNUI_PUP_SUBMENU = GNUI_SUBMENU_POINTER
};

#endif

//
// End of "$Id$".
//
