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

#ifndef GNUI_Enumerations_H
#define GNUI_Enumerations_H

# include <gnui/GNUI_API.h>
# include <gnui/GNUI_VERSION.h>

enum GNUI_Event {	// these should match gnui/events.h
  GNUI_NO_EVENT		= 0,
  GNUI_PUSH		= 1,
  GNUI_RELEASE		= 2,
  GNUI_ENTER		= 3,
  GNUI_LEAVE		= 4,
  GNUI_DRAG		= 5,
  GNUI_FOCUS		= 6,
  GNUI_UNFOCUS		= 7,
  GNUI_KEYDOWN		= 8,
  GNUI_KEYBOARD		= GNUI_KEYDOWN,
  GNUI_KEYUP		= 9,
  //GNUI_CLOSE		= 10, // not in gnui.0
  GNUI_MOVE		= 11,
  GNUI_SHORTCUT		= 12,
  GNUI_DEACTIVATE		= 13,
  GNUI_ACTIVATE		= 14,
  GNUI_HIDE		= 15,
  GNUI_SHOW		= 16,
  GNUI_PASTE		= 17,
  //GNUI_SELECTIONCLEAR	= 18, // not in gnui.0
  GNUI_MOUSEWHEEL		= 19,
  GNUI_DND_ENTER		= 20,
  GNUI_DND_DRAG		= 21,
  GNUI_DND_LEAVE		= 22,
  GNUI_DND_RELEASE	= 23
};

enum GNUI_When { // These should match values in gnui/Widget.h
  GNUI_WHEN_NEVER		= 0,
  GNUI_WHEN_CHANGED	= 1,
  GNUI_WHEN_RELEASE	= 4,
  GNUI_WHEN_RELEASE_ALWAYS= 6,
  GNUI_WHEN_ENTER_KEY	= 8,
  GNUI_WHEN_ENTER_KEY_ALWAYS=10,
  GNUI_WHEN_ENTER_KEY_CHANGED=11,
  GNUI_WHEN_NOT_CHANGED	= 2 // modifier bit to disable changed() test
};

// These should match symbols in gnui/events.h:
#define GNUI_Button	0 // old value was 0xfee8
#define GNUI_LEFT_MOUSE	1
#define GNUI_MIDDLE_MOUSE	2
#define GNUI_RIGHT_MOUSE	3
#define GNUI_BackSpace	0xff08
#define GNUI_Tab		0xff09
#define GNUI_Enter	0xff0d
#define GNUI_Pause	0xff13
#define GNUI_Scroll_Lock	0xff14
#define GNUI_Escape	0xff1b
#define GNUI_Home		0xff50
#define GNUI_Left		0xff51
#define GNUI_Up		0xff52
#define GNUI_Right	0xff53
#define GNUI_Down		0xff54
#define GNUI_Page_Up	0xff55
#define GNUI_Page_Down	0xff56
#define GNUI_End		0xff57
#define GNUI_Print	0xff61
#define GNUI_Insert	0xff63
#define GNUI_Menu		0xff67 // the "menu/apps" key on XFree86
#define GNUI_Help		0xff68 // the 'help' key on Mac keyboards
#define GNUI_Num_Lock	0xff7f
#define GNUI_KP		0xff80 // use GNUI_KP+'x' for 'x' on numeric keypad
#define GNUI_KP_Enter	0xff8d // same as GNUI_KP+'\r'
#define GNUI_KP_Last	0xffbd // use to range-check keypad
#define GNUI_F		0xffbd // use GNUI_F+n for function key n
#define GNUI_F_Last	0xffe0 // use to range-check function keys
#define GNUI_Shift_L	0xffe1
#define GNUI_Shift_R	0xffe2
#define GNUI_Control_L	0xffe3
#define GNUI_Control_R	0xffe4
#define GNUI_Caps_Lock	0xffe5
#define GNUI_Meta_L	0xffe7
#define GNUI_Meta_R	0xffe8
#define GNUI_Alt_L	0xffe9
#define GNUI_Alt_R	0xffea
#define GNUI_Delete	0xffff

#define GNUI_SHIFT	0x00010000
#define GNUI_CAPS_LOCK	0x00020000
#define GNUI_CTRL		0x00040000
#define GNUI_ALT		0x00080000
#define GNUI_NUM_LOCK	0x00100000 // most X servers do this?
#define GNUI_META		0x00400000
#define GNUI_SCROLL_LOCK	0x00800000
#define GNUI_BUTTON1	0x01000000
#define GNUI_BUTTON2	0x02000000
#define GNUI_BUTTON3	0x04000000
#define GNUI_BUTTONS	0x7f000000 // All possible buttons
#define GNUI_BUTTON(n)	(0x00800000<<(n))

#ifdef __APPLE__
#  define GNUI_COMMAND	GNUI_META
#else
#  define GNUI_COMMAND	GNUI_CTRL
#endif // __APPLE__

#include <gnui/Style.h>

typedef gnui::Box* GNUI_Boxtype;

// Box types. Many of the FRAME types are deleted in gnui.0, these have
// been replaced with the equivalent BOX which draws it's inner area:
#define GNUI_NO_BOX		gnui::NO_BOX
#define GNUI_FLAT_BOX		gnui::FLAT_BOX
#define GNUI_UP_BOX		gnui::UP_BOX
#define GNUI_DOWN_BOX		gnui::DOWN_BOX
#define GNUI_UP_FRAME		gnui::UP_BOX //
#define GNUI_DOWN_FRAME		gnui::DOWN_BOX //
#define GNUI_THIN_UP_BOX		gnui::THIN_UP_BOX
#define GNUI_THIN_DOWN_BOX	gnui::THIN_DOWN_BOX
#define GNUI_THIN_UP_FRAME	gnui::THIN_UP_BOX //
#define GNUI_THIN_DOWN_FRAME	gnui::THIN_DOWN_BOX //
#define GNUI_ENGRAVED_BOX		gnui::ENGRAVED_BOX
#define GNUI_EMBOSSED_BOX		gnui::EMBOSSED_BOX
#define GNUI_ENGRAVED_FRAME	gnui::ENGRAVED_BOX //
#define GNUI_EMBOSSED_FRAME	gnui::EMBOSSED_BOX //
#define GNUI_BORDER_BOX		gnui::BORDER_BOX
#define GNUI_SHADOW_BOX		gnui::SHADOW_BOX
#define GNUI_BORDER_FRAME		gnui::BORDER_FRAME
#define GNUI_SHADOW_FRAME		gnui::SHADOW_BOX //
#define GNUI_ROUNDED_BOX		gnui::ROUNDED_BOX
#define GNUI_RSHADOW_BOX		gnui::RSHADOW_BOX
#define GNUI_ROUNDED_FRAME	gnui::ROUNDED_BOX //
#define GNUI_RFLAT_BOX		gnui::RFLAT_BOX
#define GNUI_ROUND_UP_BOX		gnui::ROUND_UP_BOX
#define GNUI_ROUND_DOWN_BOX	gnui::ROUND_DOWN_BOX
#define GNUI_DIAMOND_UP_BOX	gnui::DIAMOND_UP_BOX
#define GNUI_DIAMOND_DOWN_BOX	gnui::DIAMOND_DOWN_BOX
#define GNUI_OVAL_BOX		gnui::OVAL_BOX
#define GNUI_OSHADOW_BOX		gnui::OSHADOW_BOX
#define GNUI_OVAL_FRAME		gnui::OVAL_BOX //
#define GNUI_OFLAT_BOX		gnui::OFLAT_BOX
#define GNUI_PLASTIC_UP_BOX	gnui::PLASTIC_UP_BOX
#define GNUI_PLASTIC_DOWN_BOX	gnui::PLASTIC_DOWN_BOX
#define GNUI_PLASTIC_UP_FRAME	gnui::PLASTIC_UP_BOX //
#define GNUI_PLASTIC_DOWN_FRAME	gnui::PLASTIC_DOWN_BOX //
//#define GNUI_FREE_BOXTYPE not used in gnui 2.0

// conversions of box types to other boxtypes:
//inline GNUI_Boxtype gnui_down(GNUI_Boxtype b) // not implemented
//inline GNUI_Boxtype gnui_frame(GNUI_Boxtype b)

// back-compatability box types:
#define GNUI_FRAME		GNUI_ENGRAVED_FRAME
#define GNUI_FRAME_BOX		GNUI_ENGRAVED_BOX
#define GNUI_CIRCLE_BOX		GNUI_ROUND_DOWN_BOX
#define GNUI_DIAMOND_BOX		GNUI_DIAMOND_DOWN_BOX

// labeltypes:
#define GNUI_NO_LABEL		gnui::NO_LABEL
#define GNUI_NORMAL_LABEL		gnui::NORMAL_LABEL
#define GNUI_SHADOW_LABEL		gnui::SHADOW_LABEL
#define GNUI_ENGRAVED_LABEL	gnui::ENGRAVED_LABEL
#define GNUI_EMBOSSED_LABEL	gnui::EMBOSSED_LABEL
//#define GNUI_FREE_LABELTYPE not used in gnui.0
#define GNUI_SYMBOL_LABEL		GNUI_NORMAL_LABEL

#define GNUI_Align		gnui::Flags
enum {
  GNUI_ALIGN_CENTER		= 0,
  GNUI_ALIGN_TOP			= gnui::ALIGN_TOP,
  GNUI_ALIGN_BOTTOM		= gnui::ALIGN_BOTTOM,
  GNUI_ALIGN_LEFT			= gnui::ALIGN_LEFT,
  GNUI_ALIGN_RIGHT		= gnui::ALIGN_RIGHT,
  GNUI_ALIGN_INSIDE		= gnui::ALIGN_INSIDE,
  GNUI_ALIGN_TEXT_OVER_IMAGE	= gnui::ALIGN_BOTTOM|gnui::ALIGN_INSIDE, //
  GNUI_ALIGN_IMAGE_OVER_TEXT	= 0,
  GNUI_ALIGN_CLIP			= gnui::ALIGN_CLIP,
  GNUI_ALIGN_WRAP			= gnui::ALIGN_WRAP,
  GNUI_ALIGN_MASK			= gnui::ALIGN_MASK,
  GNUI_ALIGN_TOP_LEFT		= GNUI_ALIGN_TOP | GNUI_ALIGN_LEFT,
  GNUI_ALIGN_TOP_RIGHT		= GNUI_ALIGN_TOP | GNUI_ALIGN_RIGHT,
  GNUI_ALIGN_BOTTOM_LEFT		= GNUI_ALIGN_BOTTOM | GNUI_ALIGN_LEFT,
  GNUI_ALIGN_BOTTOM_RIGHT		= GNUI_ALIGN_BOTTOM | GNUI_ALIGN_RIGHT,
  GNUI_ALIGN_LEFT_TOP		= GNUI_ALIGN_TOP_LEFT,
  GNUI_ALIGN_RIGHT_TOP		= GNUI_ALIGN_TOP_RIGHT,
  GNUI_ALIGN_LEFT_BOTTOM		= GNUI_ALIGN_BOTTOM_LEFT,
  GNUI_ALIGN_RIGHT_BOTTOM		= GNUI_ALIGN_BOTTOM_RIGHT,
  GNUI_ALIGN_NOWRAP		= 0
};

#define GNUI_HELVETICA		gnui::HELVETICA
#define GNUI_HELVETICA_BOLD	gnui::HELVETICA_BOLD
#define GNUI_HELVETICA_ITALIC	gnui::HELVETICA_ITALIC
#define GNUI_HELVETICA_BOLD_ITALIC gnui::HELVETICA_BOLD_ITALIC
#define GNUI_COURIER		gnui::COURIER
#define GNUI_COURIER_BOLD		gnui::COURIER_BOLD
#define GNUI_COURIER_ITALIC	gnui::COURIER_ITALIC
#define GNUI_COURIER_BOLD_ITALIC	gnui::COURIER_BOLD_ITALIC
#define GNUI_TIMES		gnui::TIMES
#define GNUI_TIMES_BOLD		gnui::TIMES_BOLD
#define GNUI_TIMES_ITALIC		gnui::TIMES_ITALIC
#define GNUI_TIMES_BOLD_ITALIC	gnui::TIMES_BOLD_ITALIC
#define GNUI_SYMBOL		gnui::SYMBOL_FONT
#define GNUI_SCREEN		gnui::SCREEN_FONT
#define GNUI_SCREEN_BOLD		gnui::SCREEN_BOLD_FONT
#define GNUI_ZAPF_DINGBATS	gnui::ZAPF_DINGBATS
//#define GNUI_FREE_FONT
// These used to be added to the above fonts but were sometimes used alone
// because GNUI_HELVETICA was zero. Only using these by themselves works now:
#define GNUI_BOLD			gnui::HELVETICA_BOLD
#define GNUI_ITALIC		gnui::HELVETICA_ITALIC

#define GNUI_NORMAL_SIZE (gnui::Widget::default_style->labelsize_)
#define GNUI_FOREGROUND_COLOR (gnui::Widget::default_style->labelcolor_)
#define GNUI_BACKGROUND2_COLOR (gnui::Widget::default_style->color_)
#define GNUI_SELECTION_COLOR (gnui::Widget::default_style->selection_color_)

#define GNUI_Color	gnui::Color
enum {
  GNUI_GRAY0		= gnui::GRAY00,
  GNUI_DARK3		= gnui::GRAY33,
  GNUI_DARK2		= gnui::GRAY60,
  GNUI_DARK1		= gnui::GRAY66,
  GNUI_GRAY		= gnui::GRAY75,
  GNUI_BACKGROUND_COLOR	= gnui::GRAY75,
  GNUI_LIGHT1		= gnui::GRAY85,
  GNUI_LIGHT2		= gnui::GRAY90,
  GNUI_LIGHT3		= gnui::GRAY99,

  GNUI_BLACK		= gnui::BLACK,
  GNUI_RED		= gnui::RED,
  GNUI_GREEN		= gnui::GREEN,
  GNUI_YELLOW		= gnui::YELLOW,
  GNUI_BLUE		= gnui::BLUE,
  GNUI_MAGENTA		= gnui::MAGENTA,
  GNUI_CYAN		= gnui::CYAN,
  GNUI_DARK_RED		= 72,

  GNUI_DARK_GREEN		= 60,
  GNUI_DARK_YELLOW	= 76,
  GNUI_DARK_BLUE		= 136,
  GNUI_DARK_MAGENTA	= 152,
  GNUI_DARK_CYAN		= 140,

  GNUI_WHITE		= gnui::WHITE,

  GNUI_FREE_COLOR		= 16,
  GNUI_NUM_FREE_COLOR	= 16,
  GNUI_GRAY_RAMP		= gnui::GRAY00,
  GNUI_NUM_GRAY		= 24,
  GNUI_COLOR_CUBE		= gnui::BLACK,
  GNUI_NUM_RED		= 5,
  GNUI_NUM_GREEN		= 8,
  GNUI_NUM_BLUE		= 5
};

#define gnui_inactive(c)		gnui::inactive(c)
#define gnui_contrast(a,b)	gnui::contrast(a,b)
#define gnui_color_average(a,b,c)	gnui::lerp(b,a,c)
#define gnui_lighter(c)		gnui::lerp(gnui::WHITE,c,.67f)
#define gnui_darker(c)		gnui::lerp(gnui::BLACK,c,.67f)
#define gnui_rgb_color		gnui::color
#define gnui_gray_ramp(i)		(gnui::GRAY00+(i))
#define gnui_color_cube(r,g,b)	(((b)*5+(r))*8+(g)+gnui::BLACK)

#include <gnui/Cursor.h>
#define GNUI_Cursor		gnui::Cursor*
#define GNUI_CURSOR_DEFAULT	gnui::CURSOR_DEFAULT
#define GNUI_CURSOR_ARROW		gnui::CURSOR_ARROW
#define GNUI_CURSOR_CROSS		gnui::CURSOR_CROSS
#define GNUI_CURSOR_WAIT		gnui::CURSOR_WAIT
#define GNUI_CURSOR_INSERT	gnui::CURSOR_INSERT
#define GNUI_CURSOR_HAND		gnui::CURSOR_HAND
#define GNUI_CURSOR_HELP		gnui::CURSOR_HELP
#define GNUI_CURSOR_MOVE		gnui::CURSOR_MOVE
#define GNUI_CURSOR_NS		gnui::CURSOR_NS
#define GNUI_CURSOR_WE		gnui::CURSOR_WE
#define GNUI_CURSOR_NWSE		gnui::CURSOR_NWSE
#define GNUI_CURSOR_NESW		gnui::CURSOR_NESW
#define GNUI_CURSOR_NO		gnui::CURSOR_NO
#define GNUI_CURSOR_NONE		gnui::CURSOR_NONE
#define GNUI_CURSOR_N		gnui::CURSOR_NS
#define GNUI_CURSOR_NE		gnui::CURSOR_NESW
#define GNUI_CURSOR_E		gnui::CURSOR_WE
#define GNUI_CURSOR_SE		gnui::CURSOR_NWSE
#define GNUI_CURSOR_S		gnui::CURSOR_NS
#define GNUI_CURSOR_SW		gnui::CURSOR_NESW
#define GNUI_CURSOR_W		gnui::CURSOR_WE
#define GNUI_CURSOR_NW		gnui::CURSOR_NWSE

enum { // must match values in gnui/run.h
  GNUI_READ = 1,
  GNUI_WRITE = 4,
  GNUI_EXCEPT = 8
};

enum GNUI_Mode { // must match values in gnui/visual.h
  GNUI_RGB	= 0,
  GNUI_INDEX	= 1,
  GNUI_SINGLE	= 0,
  GNUI_DOUBLE	= 2,
  GNUI_ACCUM	= 4,
  GNUI_ALPHA	= 8,
  GNUI_DEPTH	= 16,
  GNUI_STENCIL	= 32,
  GNUI_RGB8	= 64,
  GNUI_MULTISAMPLE= 128,
  GNUI_STEREO     = 256,
  GNUI_FAKE_SINGLE = 512	// Fake single buffered windows using double-buffer
};

#include <gnui/damage.h>
enum GNUI_Damage {
  GNUI_DAMAGE_CHILD    = gnui::DAMAGE_CHILD,
  GNUI_DAMAGE_EXPOSE   = gnui::DAMAGE_EXPOSE,
  GNUI_DAMAGE_SCROLL   = gnui::DAMAGE_SCROLL,
  GNUI_DAMAGE_OVERLAY  = gnui::DAMAGE_OVERLAY,
  GNUI_DAMAGE_ALL      = gnui::DAMAGE_ALL
};

// FLTK 1.0.x compatibility definitions...
#  ifdef FLTK_1_0_COMPAT
#    define contrast	gnui_contrast
#    define down	gnui_down
#    define frame	gnui_frame
#    define inactive	gnui_inactive
#  endif // FLTK_1_0_COMPAT

#endif

//
// End of "$Id$".
//
