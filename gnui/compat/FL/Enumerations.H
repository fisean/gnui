//
// "$Id$"
//
// Enumerations for the Fast Light Tool Kit (FLTK).
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

#ifndef Fl_Enumerations_H
#define Fl_Enumerations_H

# include <gnui/FL_API.h>
# include <gnui/FL_VERSION.h>

enum Fl_Event {	// these should match gnui/events.h
  FL_NO_EVENT		= 0,
  FL_PUSH		= 1,
  FL_RELEASE		= 2,
  FL_ENTER		= 3,
  FL_LEAVE		= 4,
  FL_DRAG		= 5,
  FL_FOCUS		= 6,
  FL_UNFOCUS		= 7,
  FL_KEYDOWN		= 8,
  FL_KEYBOARD		= FL_KEYDOWN,
  FL_KEYUP		= 9,
  //FL_CLOSE		= 10, // not in gnui.0
  FL_MOVE		= 11,
  FL_SHORTCUT		= 12,
  FL_DEACTIVATE		= 13,
  FL_ACTIVATE		= 14,
  FL_HIDE		= 15,
  FL_SHOW		= 16,
  FL_PASTE		= 17,
  //FL_SELECTIONCLEAR	= 18, // not in gnui.0
  FL_MOUSEWHEEL		= 19,
  FL_DND_ENTER		= 20,
  FL_DND_DRAG		= 21,
  FL_DND_LEAVE		= 22,
  FL_DND_RELEASE	= 23
};

enum Fl_When { // These should match values in gnui/Widget.h
  FL_WHEN_NEVER		= 0,
  FL_WHEN_CHANGED	= 1,
  FL_WHEN_RELEASE	= 4,
  FL_WHEN_RELEASE_ALWAYS= 6,
  FL_WHEN_ENTER_KEY	= 8,
  FL_WHEN_ENTER_KEY_ALWAYS=10,
  FL_WHEN_ENTER_KEY_CHANGED=11,
  FL_WHEN_NOT_CHANGED	= 2 // modifier bit to disable changed() test
};

// These should match symbols in gnui/events.h:
#define FL_Button	0 // old value was 0xfee8
#define FL_LEFT_MOUSE	1
#define FL_MIDDLE_MOUSE	2
#define FL_RIGHT_MOUSE	3
#define FL_BackSpace	0xff08
#define FL_Tab		0xff09
#define FL_Enter	0xff0d
#define FL_Pause	0xff13
#define FL_Scroll_Lock	0xff14
#define FL_Escape	0xff1b
#define FL_Home		0xff50
#define FL_Left		0xff51
#define FL_Up		0xff52
#define FL_Right	0xff53
#define FL_Down		0xff54
#define FL_Page_Up	0xff55
#define FL_Page_Down	0xff56
#define FL_End		0xff57
#define FL_Print	0xff61
#define FL_Insert	0xff63
#define FL_Menu		0xff67 // the "menu/apps" key on XFree86
#define FL_Help		0xff68 // the 'help' key on Mac keyboards
#define FL_Num_Lock	0xff7f
#define FL_KP		0xff80 // use FL_KP+'x' for 'x' on numeric keypad
#define FL_KP_Enter	0xff8d // same as Fl_KP+'\r'
#define FL_KP_Last	0xffbd // use to range-check keypad
#define FL_F		0xffbd // use FL_F+n for function key n
#define FL_F_Last	0xffe0 // use to range-check function keys
#define FL_Shift_L	0xffe1
#define FL_Shift_R	0xffe2
#define FL_Control_L	0xffe3
#define FL_Control_R	0xffe4
#define FL_Caps_Lock	0xffe5
#define FL_Meta_L	0xffe7
#define FL_Meta_R	0xffe8
#define FL_Alt_L	0xffe9
#define FL_Alt_R	0xffea
#define FL_Delete	0xffff

#define FL_SHIFT	0x00010000
#define FL_CAPS_LOCK	0x00020000
#define FL_CTRL		0x00040000
#define FL_ALT		0x00080000
#define FL_NUM_LOCK	0x00100000 // most X servers do this?
#define FL_META		0x00400000
#define FL_SCROLL_LOCK	0x00800000
#define FL_BUTTON1	0x01000000
#define FL_BUTTON2	0x02000000
#define FL_BUTTON3	0x04000000
#define FL_BUTTONS	0x7f000000 // All possible buttons
#define FL_BUTTON(n)	(0x00800000<<(n))

#ifdef __APPLE__
#  define FL_COMMAND	FL_META
#else
#  define FL_COMMAND	FL_CTRL
#endif // __APPLE__

#include <gnui/Style.h>

typedef gnui::Box* Fl_Boxtype;

// Box types. Many of the FRAME types are deleted in gnui.0, these have
// been replaced with the equivalent BOX which draws it's inner area:
#define FL_NO_BOX		gnui::NO_BOX
#define FL_FLAT_BOX		gnui::FLAT_BOX
#define FL_UP_BOX		gnui::UP_BOX
#define FL_DOWN_BOX		gnui::DOWN_BOX
#define FL_UP_FRAME		gnui::UP_BOX //
#define FL_DOWN_FRAME		gnui::DOWN_BOX //
#define FL_THIN_UP_BOX		gnui::THIN_UP_BOX
#define FL_THIN_DOWN_BOX	gnui::THIN_DOWN_BOX
#define FL_THIN_UP_FRAME	gnui::THIN_UP_BOX //
#define FL_THIN_DOWN_FRAME	gnui::THIN_DOWN_BOX //
#define FL_ENGRAVED_BOX		gnui::ENGRAVED_BOX
#define FL_EMBOSSED_BOX		gnui::EMBOSSED_BOX
#define FL_ENGRAVED_FRAME	gnui::ENGRAVED_BOX //
#define FL_EMBOSSED_FRAME	gnui::EMBOSSED_BOX //
#define FL_BORDER_BOX		gnui::BORDER_BOX
#define FL_SHADOW_BOX		gnui::SHADOW_BOX
#define FL_BORDER_FRAME		gnui::BORDER_FRAME
#define FL_SHADOW_FRAME		gnui::SHADOW_BOX //
#define FL_ROUNDED_BOX		gnui::ROUNDED_BOX
#define FL_RSHADOW_BOX		gnui::RSHADOW_BOX
#define FL_ROUNDED_FRAME	gnui::ROUNDED_BOX //
#define FL_RFLAT_BOX		gnui::RFLAT_BOX
#define FL_ROUND_UP_BOX		gnui::ROUND_UP_BOX
#define FL_ROUND_DOWN_BOX	gnui::ROUND_DOWN_BOX
#define FL_DIAMOND_UP_BOX	gnui::DIAMOND_UP_BOX
#define FL_DIAMOND_DOWN_BOX	gnui::DIAMOND_DOWN_BOX
#define FL_OVAL_BOX		gnui::OVAL_BOX
#define FL_OSHADOW_BOX		gnui::OSHADOW_BOX
#define FL_OVAL_FRAME		gnui::OVAL_BOX //
#define FL_OFLAT_BOX		gnui::OFLAT_BOX
#define FL_PLASTIC_UP_BOX	gnui::PLASTIC_UP_BOX
#define FL_PLASTIC_DOWN_BOX	gnui::PLASTIC_DOWN_BOX
#define FL_PLASTIC_UP_FRAME	gnui::PLASTIC_UP_BOX //
#define FL_PLASTIC_DOWN_FRAME	gnui::PLASTIC_DOWN_BOX //
//#define FL_FREE_BOXTYPE not used in gnui 2.0

// conversions of box types to other boxtypes:
//inline Fl_Boxtype fl_down(Fl_Boxtype b) // not implemented
//inline Fl_Boxtype fl_frame(Fl_Boxtype b)

// back-compatability box types:
#define FL_FRAME		FL_ENGRAVED_FRAME
#define FL_FRAME_BOX		FL_ENGRAVED_BOX
#define FL_CIRCLE_BOX		FL_ROUND_DOWN_BOX
#define FL_DIAMOND_BOX		FL_DIAMOND_DOWN_BOX

// labeltypes:
#define FL_NO_LABEL		gnui::NO_LABEL
#define FL_NORMAL_LABEL		gnui::NORMAL_LABEL
#define FL_SHADOW_LABEL		gnui::SHADOW_LABEL
#define FL_ENGRAVED_LABEL	gnui::ENGRAVED_LABEL
#define FL_EMBOSSED_LABEL	gnui::EMBOSSED_LABEL
//#define FL_FREE_LABELTYPE not used in gnui.0
#define FL_SYMBOL_LABEL		FL_NORMAL_LABEL

#define Fl_Align		gnui::Flags
enum {
  FL_ALIGN_CENTER		= 0,
  FL_ALIGN_TOP			= gnui::ALIGN_TOP,
  FL_ALIGN_BOTTOM		= gnui::ALIGN_BOTTOM,
  FL_ALIGN_LEFT			= gnui::ALIGN_LEFT,
  FL_ALIGN_RIGHT		= gnui::ALIGN_RIGHT,
  FL_ALIGN_INSIDE		= gnui::ALIGN_INSIDE,
  FL_ALIGN_TEXT_OVER_IMAGE	= gnui::ALIGN_BOTTOM|gnui::ALIGN_INSIDE, //
  FL_ALIGN_IMAGE_OVER_TEXT	= 0,
  FL_ALIGN_CLIP			= gnui::ALIGN_CLIP,
  FL_ALIGN_WRAP			= gnui::ALIGN_WRAP,
  FL_ALIGN_MASK			= gnui::ALIGN_MASK,
  FL_ALIGN_TOP_LEFT		= FL_ALIGN_TOP | FL_ALIGN_LEFT,
  FL_ALIGN_TOP_RIGHT		= FL_ALIGN_TOP | FL_ALIGN_RIGHT,
  FL_ALIGN_BOTTOM_LEFT		= FL_ALIGN_BOTTOM | FL_ALIGN_LEFT,
  FL_ALIGN_BOTTOM_RIGHT		= FL_ALIGN_BOTTOM | FL_ALIGN_RIGHT,
  FL_ALIGN_LEFT_TOP		= FL_ALIGN_TOP_LEFT,
  FL_ALIGN_RIGHT_TOP		= FL_ALIGN_TOP_RIGHT,
  FL_ALIGN_LEFT_BOTTOM		= FL_ALIGN_BOTTOM_LEFT,
  FL_ALIGN_RIGHT_BOTTOM		= FL_ALIGN_BOTTOM_RIGHT,
  FL_ALIGN_NOWRAP		= 0
};

#define FL_HELVETICA		gnui::HELVETICA
#define FL_HELVETICA_BOLD	gnui::HELVETICA_BOLD
#define FL_HELVETICA_ITALIC	gnui::HELVETICA_ITALIC
#define FL_HELVETICA_BOLD_ITALIC gnui::HELVETICA_BOLD_ITALIC
#define FL_COURIER		gnui::COURIER
#define FL_COURIER_BOLD		gnui::COURIER_BOLD
#define FL_COURIER_ITALIC	gnui::COURIER_ITALIC
#define FL_COURIER_BOLD_ITALIC	gnui::COURIER_BOLD_ITALIC
#define FL_TIMES		gnui::TIMES
#define FL_TIMES_BOLD		gnui::TIMES_BOLD
#define FL_TIMES_ITALIC		gnui::TIMES_ITALIC
#define FL_TIMES_BOLD_ITALIC	gnui::TIMES_BOLD_ITALIC
#define FL_SYMBOL		gnui::SYMBOL_FONT
#define FL_SCREEN		gnui::SCREEN_FONT
#define FL_SCREEN_BOLD		gnui::SCREEN_BOLD_FONT
#define FL_ZAPF_DINGBATS	gnui::ZAPF_DINGBATS
//#define FL_FREE_FONT
// These used to be added to the above fonts but were sometimes used alone
// because FL_HELVETICA was zero. Only using these by themselves works now:
#define FL_BOLD			gnui::HELVETICA_BOLD
#define FL_ITALIC		gnui::HELVETICA_ITALIC

#define FL_NORMAL_SIZE (gnui::Widget::default_style->labelsize_)
#define FL_FOREGROUND_COLOR (gnui::Widget::default_style->labelcolor_)
#define FL_BACKGROUND2_COLOR (gnui::Widget::default_style->color_)
#define FL_SELECTION_COLOR (gnui::Widget::default_style->selection_color_)

#define Fl_Color	gnui::Color
enum {
  FL_GRAY0		= gnui::GRAY00,
  FL_DARK3		= gnui::GRAY33,
  FL_DARK2		= gnui::GRAY60,
  FL_DARK1		= gnui::GRAY66,
  FL_GRAY		= gnui::GRAY75,
  FL_BACKGROUND_COLOR	= gnui::GRAY75,
  FL_LIGHT1		= gnui::GRAY85,
  FL_LIGHT2		= gnui::GRAY90,
  FL_LIGHT3		= gnui::GRAY99,

  FL_BLACK		= gnui::BLACK,
  FL_RED		= gnui::RED,
  FL_GREEN		= gnui::GREEN,
  FL_YELLOW		= gnui::YELLOW,
  FL_BLUE		= gnui::BLUE,
  FL_MAGENTA		= gnui::MAGENTA,
  FL_CYAN		= gnui::CYAN,
  FL_DARK_RED		= 72,

  FL_DARK_GREEN		= 60,
  FL_DARK_YELLOW	= 76,
  FL_DARK_BLUE		= 136,
  FL_DARK_MAGENTA	= 152,
  FL_DARK_CYAN		= 140,

  FL_WHITE		= gnui::WHITE,

  FL_FREE_COLOR		= 16,
  FL_NUM_FREE_COLOR	= 16,
  FL_GRAY_RAMP		= gnui::GRAY00,
  FL_NUM_GRAY		= 24,
  FL_COLOR_CUBE		= gnui::BLACK,
  FL_NUM_RED		= 5,
  FL_NUM_GREEN		= 8,
  FL_NUM_BLUE		= 5
};

#define fl_inactive(c)		gnui::inactive(c)
#define fl_contrast(a,b)	gnui::contrast(a,b)
#define fl_color_average(a,b,c)	gnui::lerp(b,a,c)
#define fl_lighter(c)		gnui::lerp(gnui::WHITE,c,.67f)
#define fl_darker(c)		gnui::lerp(gnui::BLACK,c,.67f)
#define fl_rgb_color		gnui::color
#define fl_gray_ramp(i)		(gnui::GRAY00+(i))
#define fl_color_cube(r,g,b)	(((b)*5+(r))*8+(g)+gnui::BLACK)

#include <gnui/Cursor.h>
#define Fl_Cursor		gnui::Cursor*
#define FL_CURSOR_DEFAULT	gnui::CURSOR_DEFAULT
#define FL_CURSOR_ARROW		gnui::CURSOR_ARROW
#define FL_CURSOR_CROSS		gnui::CURSOR_CROSS
#define FL_CURSOR_WAIT		gnui::CURSOR_WAIT
#define FL_CURSOR_INSERT	gnui::CURSOR_INSERT
#define FL_CURSOR_HAND		gnui::CURSOR_HAND
#define FL_CURSOR_HELP		gnui::CURSOR_HELP
#define FL_CURSOR_MOVE		gnui::CURSOR_MOVE
#define FL_CURSOR_NS		gnui::CURSOR_NS
#define FL_CURSOR_WE		gnui::CURSOR_WE
#define FL_CURSOR_NWSE		gnui::CURSOR_NWSE
#define FL_CURSOR_NESW		gnui::CURSOR_NESW
#define FL_CURSOR_NO		gnui::CURSOR_NO
#define FL_CURSOR_NONE		gnui::CURSOR_NONE
#define FL_CURSOR_N		gnui::CURSOR_NS
#define FL_CURSOR_NE		gnui::CURSOR_NESW
#define FL_CURSOR_E		gnui::CURSOR_WE
#define FL_CURSOR_SE		gnui::CURSOR_NWSE
#define FL_CURSOR_S		gnui::CURSOR_NS
#define FL_CURSOR_SW		gnui::CURSOR_NESW
#define FL_CURSOR_W		gnui::CURSOR_WE
#define FL_CURSOR_NW		gnui::CURSOR_NWSE

enum { // must match values in gnui/run.h
  FL_READ = 1,
  FL_WRITE = 4,
  FL_EXCEPT = 8
};

enum Fl_Mode { // must match values in gnui/visual.h
  FL_RGB	= 0,
  FL_INDEX	= 1,
  FL_SINGLE	= 0,
  FL_DOUBLE	= 2,
  FL_ACCUM	= 4,
  FL_ALPHA	= 8,
  FL_DEPTH	= 16,
  FL_STENCIL	= 32,
  FL_RGB8	= 64,
  FL_MULTISAMPLE= 128,
  FL_STEREO     = 256,
  FL_FAKE_SINGLE = 512	// Fake single buffered windows using double-buffer
};

#include <gnui/damage.h>
enum Fl_Damage {
  FL_DAMAGE_CHILD    = gnui::DAMAGE_CHILD,
  FL_DAMAGE_EXPOSE   = gnui::DAMAGE_EXPOSE,
  FL_DAMAGE_SCROLL   = gnui::DAMAGE_SCROLL,
  FL_DAMAGE_OVERLAY  = gnui::DAMAGE_OVERLAY,
  FL_DAMAGE_ALL      = gnui::DAMAGE_ALL
};

// FLTK 1.0.x compatibility definitions...
#  ifdef FLTK_1_0_COMPAT
#    define contrast	fl_contrast
#    define down	fl_down
#    define frame	fl_frame
#    define inactive	fl_inactive
#  endif // FLTK_1_0_COMPAT

#endif

//
// End of "$Id$".
//
