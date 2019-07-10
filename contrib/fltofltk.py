#!/bin/python
#
# "$Id: $"
# 
# fltofltk.py -- convert FLTK 1.x code to FLTK 2.x
#
# Copyright(C) 2005 Chris Warren-Smith. Gawler, South Australia
# cwarrens@twpo.com.au
#
# This program is distributed under the terms of the GPL v2.0 or later
# Download the GNU Public License (GPL) from www.gnu.org
#

import sys
import os
import glob
import re
import shutil

backupDir = "v1src.bak"
version = "$Revision: 0.2 $";
versionStr = version.replace("Revision:", "").replace("$", "")
codeComment = "// Converted to FLTK~2 using fltofltk.py version"+versionStr+ "\n"

GNUI_INCLUDE="\
\n//TODO: delete unused header files\
\n#include <fltk/events.h>\
\n#include <fltk/run.h>\
\n#include <fltk/events.h>\
\n#include <fltk/Color.h>\
\n#include <fltk/Font.h>\
\n#include <fltk/Box.h>\
\n#include <fltk/error.h>\
\n#include <fltk/visual.h>\
\n#include <fltk/damage.h>\
\n#include <fltk/filename.h>\
\n#include <fltk/Cursor.h>\
"

SCROLL_INCLUDE="\
#include <fltk/ScrollGroup.h>\
\n#include <fltk/Scrollbar.h>\
"

def refactor(s, oldfunc, newfunc, numargs):
   # patch oldfunc function calls in s with newfunc calls
   # eg foo_func(x) -> setFoo(x);
   nextIndex = 0
   while 1:
      i = s.find(oldfunc, nextIndex)
      if (i == -1):
         break
      argBegin = s.find("(", i)
      if (argBegin == -1):
         break;
      argEnd = s.find(")", argBegin)
      if (argEnd == -1):
         break;

      # check to ensure oldfunc and '(' are on the same line
      lineBreak = s.find("\n", i)
      if (lineBreak < argBegin):
         nextIndex = lineBreak+1
         continue

      # create a list of program arguments
      args = s[argBegin+1:argEnd]
      argList = []
      if (len(args) > 0):
         nextWord = ""           
         for c in args:
            if (c == ','):
               argList.append(nextWord)
               nextWord = ""
            else:
               nextWord = nextWord+c
         argList.append(nextWord)

      # check this is the desired overload/signature           
      if (len(argList) != numargs):
         nextIndex = argEnd
         continue

      # replace the argument place-holders in newfunc with the
      # existing code arguments from the v1 code
      for argn in range(1, numargs+1):
         newfuncCode = re.sub(str(argn), argList[argn-1], newfunc)

      # update the next code string
      s = s[:i]+newfuncCode+s[argEnd+1:]
      nextIndex = i+len(newfuncCode)
   return s

def noopCode(s, oldfunc):
   # remove the entire call to the given function
   nextIndex = 0
   while 1:
      i = s.find(oldfunc, nextIndex)
      if (i == -1):
         break
      iend = s.find("(", i)
      if (iend == -1):
         break;
      iend = s.find(")", iend)
      if (iend == -1):
         break;
      iend = s.find(";", iend)
      if (iend == -1):
         break;
      # update the next code string
      s = s[:i]+s[iend+1:]
      nextIndex = i
   return s

def processHashDefines(s):
   # process #define convervions from FL mapping headers
   s = s.replace("GNUI_UP_FRAME", "UP_BOX")
   s = s.replace("GNUI_DOWN_FRAME", "DOWN_BOX")
   s = s.replace("GNUI_THIN_UP_FRAME", "THIN_UP_BOX")
   s = s.replace("GNUI_THIN_DOWN_FRAME", "THIN_DOWN_BOX")
   s = s.replace("GNUI_ENGRAVED_FRAME", "ENGRAVED_BOX")
   s = s.replace("GNUI_EMBOSSED_FRAME", "EMBOSSED_BOX")
   s = s.replace("GNUI_ROUNDED_FRAME", "ROUNDED_BOX")
   s = s.replace("GNUI_OVAL_FRAME", "OVAL_BOX")
   s = s.replace("GNUI_PLASTIC_UP_FRAME", "PLASTIC_UP_BOX")
   s = s.replace("GNUI_PLASTIC_DOWN_FRAME", "PLASTIC_DOWN_BOX")
   s = s.replace("GNUI_FRAME", "GNUI_ENGRAVED_FRAME")
   s = s.replace("GNUI_FRAME_BOX", "GNUI_ENGRAVED_BOX")
   s = s.replace("GNUI_CIRCLE_BOX", "GNUI_ROUND_DOWN_BOX")
   s = s.replace("GNUI_DIAMOND_BOX", "GNUI_DIAMOND_DOWN_BOX")
   s = s.replace("GNUI_SYMBOL_LABEL", "GNUI_NORMAL_LABEL")
   s = s.replace("GNUI_Align", "Flags")
   s = s.replace("GNUI_SYMBOL", "SYMBOL_FONT")
   s = s.replace("GNUI_SCREEN", "SCREEN_FONT")
   s = s.replace("GNUI_SCREEN_BOLD", "SCREEN_BOLD_FONT")
   s = s.replace("GNUI_BOLD", "HELVETICA_BOLD")
   s = s.replace("GNUI_ITALIC", "HELVETICA_ITALIC")
   s = s.replace("GNUI_NORMAL_SIZE", "(Widget::default_style->labelsize())")
   s = s.replace("GNUI_FOREGROUND_COLOR", "(Widget::default_style->labelcolor_)")
   s = s.replace("GNUI_BACKGROUND2_COLOR", "(Widget::default_style->color_)")
   s = s.replace("GNUI_SELECTION_COLOR", "(Widget::default_style->selection_color_)")
   s = s.replace("gnui_color_average", "lerp")
   s = s.replace("gnui_lighter", "lerp(WHITE,1,.67f)", 1)
   s = s.replace("gnui_darker", "lerp(BLACK,1,.67f)", 1)
   s = s.replace("gnui_rgb_color", "color")
   s = refactor(s, "gnui_gray_ramp", "(GRAY00+(1))", 1)
   s = s.replace("GNUI_Cursor", "Cursor*")
   s = s.replace("GNUI_CURSOR_N", "CURSOR_NS")
   s = s.replace("GNUI_CURSOR_NE", "CURSOR_NESW")
   s = s.replace("GNUI_CURSOR_E", "CURSOR_WE")
   s = s.replace("GNUI_CURSOR_SE", "CURSOR_NWSE")
   s = s.replace("GNUI_CURSOR_S", "CURSOR_NS")
   s = s.replace("GNUI_CURSOR_SW", "CURSOR_NESW")
   s = s.replace("GNUI_CURSOR_W", "CURSOR_WE")
   s = s.replace("GNUI_CURSOR_NW", "CURSOR_NWSE")
   s = s.replace("GNUI_FILLED_CHART",  "GNUI_FILL_CHART")
   s = s.replace("gnui_mult_matrix", "concat")
   s = s.replace("gnui_begin_points", "newpath")
   s = s.replace("gnui_begin_line", "newpath")
   s = s.replace("gnui_begin_loop", "newpath")
   s = s.replace("gnui_begin_polygon", "newpath")
   s = s.replace("gnui_vertex", "addvertex")
   s = s.replace("gnui_curve", "addcurve")
   s = s.replace("gnui_circle", "addcircle")
   s = s.replace("gnui_end_points", "drawpoints")
   s = s.replace("gnui_end_line", "strokepath")
   s = s.replace("gnui_end_polygon", "fillpath")
   s = s.replace("gnui_begin_complex_polygon", "newpath")
   s = s.replace("gnui_gap", "closepath")
   s = s.replace("gnui_end_complex_polygon", "fillpath")
   s = s.replace("gnui_draw_pixmap", "draw_xpm")
   s = s.replace("gnui_measure_pixmap", "measure_xpm")
   s = s.replace("gnui_scroll", "scrollrect")
   s = s.replace("gnui_shortcut_label", "key_name")
   s = s.replace("GNUI_WHEN_NEEDED", "GNUI_AUTO")
   s = s.replace("GNUI_LCOL", "BLACK")
   s = s.replace("GNUI_COL1", "GRAY75")
   s = s.replace("GNUI_MCOL", "GRAY85")
   s = s.replace("GNUI_LEFT_BCOL", "GRAY99")
   s = s.replace("GNUI_TOP_BCOL", "GRAY90")
   s = s.replace("GNUI_BOTTOM_BCOL", "GRAY35")
   s = s.replace("GNUI_RIGHT_BCOL", "GRAY20")
   s = s.replace("GNUI_INACTIVE", "GRAY66")
   s = s.replace("GNUI_INACTIVE_COL", "GRAY66")
   s = s.replace("GNUI_FREE_COL1", "Color(16)")
   s = s.replace("GNUI_FREE_COL2", "Color(17)")
   s = s.replace("GNUI_FREE_COL3", "Color(18)")
   s = s.replace("GNUI_FREE_COL4", "Color(19)")
   s = s.replace("GNUI_FREE_COL5", "Color(20)")
   s = s.replace("GNUI_FREE_COL6", "Color(21)")
   s = s.replace("GNUI_FREE_COL7", "Color(22)")
   s = s.replace("GNUI_FREE_COL8", "Color(23)")
   s = s.replace("GNUI_FREE_COL9", "Color(24)")
   s = s.replace("GNUI_FREE_COL10", "Color(25)")
   s = s.replace("GNUI_FREE_COL11", "Color(26)")
   s = s.replace("GNUI_FREE_COL12", "Color(27)")
   s = s.replace("GNUI_FREE_COL13", "Color(28)")
   s = s.replace("GNUI_FREE_COL14", "Color(29)")
   s = s.replace("GNUI_FREE_COL15", "Color(30)")
   s = s.replace("GNUI_FREE_COL16", "Color(31)")
   s = s.replace("GNUI_TOMATO", "Color(131)")
   s = s.replace("GNUI_INDIANRED", "Color(164)")
   s = s.replace("GNUI_SLATEBLUE", "Color(195)")
   s = s.replace("GNUI_DARKGOLD", "Color(84)")
   s = s.replace("GNUI_PALEGREEN", "Color(157)")
   s = s.replace("GNUI_ORCHID", "Color(203)")
   s = s.replace("GNUI_DARKCYAN", "Color(189)")
   s = s.replace("GNUI_DARKTOMATO", "Color(113)")
   s = s.replace("GNUI_WHEAT", "Color(174)")
   s = s.replace("GNUI_ALIGN_BESIDE", "ALIGN_INSIDE")
   s = s.replace("GNUI_NO_FRAME", "NO_BOX")
   s = s.replace("GNUI_ROUNDED3D_UPBOX", "ROUND_UP_BOX")
   s = s.replace("GNUI_ROUNDED3D_DOWNBOX", "ROUND_DOWN_BOX")
   s = s.replace("GNUI_OVAL3D_UPBOX", "ROUND_UP_BOX")
   s = s.replace("GNUI_OVAL3D_DOWNBOX", "ROUND_DOWN_BOX")
   s = s.replace("GNUI_DEFAULT_SIZE", "GNUI_SMALL_SIZE")
   s = s.replace("GNUI_TINY_FONT", "GNUI_TINY_SIZE")
   s = s.replace("GNUI_SMALL_FONT", "GNUI_SMALL_SIZE")
   s = s.replace("GNUI_NORMAL_FONT", "GNUI_NORMAL_SIZE")
   s = s.replace("GNUI_MEDIUM_FONT", "GNUI_MEDIUM_SIZE")
   s = s.replace("GNUI_LARGE_FONT", "GNUI_LARGE_SIZE")
   s = s.replace("GNUI_HUGE_FONT", "GNUI_HUGE_SIZE")
   s = s.replace("GNUI_NORMAL_FONT1", "GNUI_SMALL_FONT")
   s = s.replace("GNUI_NORMAL_FONT2", "GNUI_NORMAL_FONT")
   s = s.replace("GNUI_DEFAULT_FONT", "GNUI_SMALL_FONT")
   s = s.replace("GNUI_RETURN_END_CHANGED", "GNUI_WHEN_RELEASE")
   s = s.replace("GNUI_RETURN_CHANGED", "GNUI_WHEN_CHANGED")
   s = s.replace("GNUI_RETURN_END", "GNUI_WHEN_RELEASE_ALWAYS")
   s = s.replace("GNUI_RETURN_ALWAYS", "(GNUI_WHEN_CHANGED|GNUI_WHEN_NOT_CHANGED)")
   s = s.replace("GNUI_CMD_OPT", "void")
   s = s.replace("gnui_set_object_focus", "gnui_set_focus_object")
   s = s.replace("gnui_set_object_lcolor", "gnui_set_object_lcol")
   s = s.replace("gnui_set_object_align", "gnui_set_object_lalign")
   s = s.replace("gnui_set_call_back", "gnui_set_object_callback")
   s = s.replace("resizebox", "_ddfdesign_kludge()")
   s = s.replace("gnui_set_initial_placement", "gnui_set_form_geometry")
   s = s.replace("GNUI_PLACE_FREE_CENTER", "(GNUI_PLACE_CENTER|GNUI_FREE_SIZE)")
   s = s.replace("GNUI_PLACE_CENTERFREE", "(GNUI_PLACE_CENTER|GNUI_FREE_SIZE)")
   s = s.replace("gnui_prepare_form_window", "gnui_show_form")
   s = s.replace("gnui_set_form_call_back", "gnui_set_form_callback")
   s = s.replace("gnui_mousebutton", "gnui_mouse_button")
   s = s.replace("gnui_set_clipping", "gnui_clip")
   s = s.replace("gnui_unset_clipping", "gnui_pop_clip")
   s = s.replace("GNUI_NORMAL_BITMAP", "GNUI_NO_BOX")
   s = s.replace("GNUI_NORMAL_PIXMAP", "GNUI_NO_BOX")
   s = s.replace("GNUI_PUSH_BUTTON", "GNUI_TOGGLE_BUTTON")
   s = s.replace("gnui_set_button_shortcut", "gnui_set_object_shortcut")
   s = s.replace("gnui_set_chart_lcol", "gnui_set_chart_lcolor")
   s = s.replace("GNUI_INVISIBLE_CURSOR", "GNUI_CURSOR_NONE")
   s = s.replace("GNUI_DEFAULT_CURSOR", "GNUI_CURSOR_DEFAULT")
   s = s.replace("GNUI_DIAL_COL1", "GNUI_GRAY")
   s = s.replace("gnui_show_messages", "gnui_message")
   s = s.replace("GNUI_HOR_BROWSER_SLIDER", "GNUI_HOR_SLIDER")
   s = s.replace("GNUI_VERT_BROWSER_SLIDER", "GNUI_VERT_SLIDER")
   s = s.replace("GNUI_SLIDER_COL1", "GNUI_GRAY")
   s = s.replace("GNUI_NORMAL_TEXT", "GNUI_NO_BOX")
   s = s.replace("gl_start", "glstart")
   s = s.replace("gl_finish", "glfinish")
   s = s.replace("gl_color", "glsetcolor")
   s = s.replace("gl_rect", "glstrokerect")
   s = s.replace("gl_rectf", "glfillrect")
   s = s.replace("gl_font", "glsetfont")
   s = s.replace("gl_descent", "glgetdescent")
   s = s.replace("gl_width", "glgetwidth")
   s = s.replace("gl_draw", "gldrawtext")
   s = s.replace("gl_draw_image", "gldrawimage")
   s = s.replace("CHECKED", "GNUI_MENU_CHECK")
   s = s.replace("UNCHECKED", "GNUI_MENU_BOX")
   s = s.replace("DISABLED", "GNUI_MENU_INACTIVE")
   s = s.replace("GNUI_X", "CreatedWindow")
   s = s.replace("gnui_display", "xdisplay")
   s = s.replace("gnui_screen", "xscreen")
   s = s.replace("gnui_xevent", "(&xevent)")
   s = s.replace("gnui_colormap", "xcolormap")
   s = s.replace("gnui_open_display", "open_display")
   s = s.replace("gnui_visual", "xvisual")
   s = s.replace("gnui_window", "xwindow")
   return s

def processInlines(s):
   # process simple single-line inline convervions from FL mapping headers
   s = s.replace("Fl::x()", "Monitor::all().x()")
   s = s.replace("Fl::y()", "Monitor::all().y()")
   s = s.replace("Fl::w()", "Monitor::all().w()")
   s = s.replace("Fl::h()", "Monitor::all().x()")
   s = s.replace("get_color", "/*FIXME:get_color_index|split_color */")
   s = refactor(s, "get_font_sizes", "sizes", 0)
   s = refactor(s, "box_dx", "1->dx()", 1)
   s = refactor(s, "box_dy", "1->dy()", 1)
   s = refactor(s, "box_dw", "1->dw()", 1)
   s = refactor(s, "box_dh", "1->dh()", 1)
   s = refactor(s, "event_key", "event_key_state(1)", 1)

   # process gnui_draw.H (TODO complete me)
   s = s.replace("gnui_color", "setcolor /*FIXME:getcolor*/")
   s = s.replace("gnui_push_clip", "push_clip(Rectangle")
   s = s.replace("gnui_not_clipped", "not_clipped(Rectangle")
   s = s.replace("gnui_point", "addvertex /*FIXME:drawpoints();*/")
   s = s.replace("gnui_rect", "strokerect(Rectangle")
   s = s.replace("gnui_rectf", "fillrect(Rectangle")
   s = s.replace("gnui_line", "drawline")
   s = s.replace("gnui_xyline", "drawline /*FIXME:addvertex|strokepath*/")
   s = s.replace("gnui_yxline", "drawline /*FIXME:addvertex|strokepath*/")
   s = s.replace("gnui_arc", "addchord(Rectangle /*FIXME:strokepath*/")
   s = s.replace("gnui_pie", "addpie(Rectangle /*FIXME:fillpath*/")
   s = s.replace("gnui_chord", "addchord(Rectangle /*FIXME:fillpath*/")
   s = s.replace("gnui_end_loop()", "fltk::closepath();fltk::strokepath()")
   s = s.replace("gnui_font", "setfont /*FIXME:getfont*/")
   s = s.replace("gnui_size", "getsize")
   s = s.replace("gnui_height()", "getascent()+getdescent()")
   s = s.replace("gnui_descent", "getdescent")
   s = s.replace("gnui_width", "getwidth")
   s = s.replace("gnui_draw", "drawtext")
   s = s.replace("gnui_draw_image", "drawimage")
   s = s.replace("gnui_read_image", "readimage")
   s = refactor(s, "gnui_rectf", "setcolor(fltk::color(5,6,7));fillrect(Rectangle(1,2,3,4))", 7)
   s = s.replace("gnui_set_idle_callback", "set_idle")
   s = s.replace("gnui_do_only_forms", "gnui_do_forms")
   s = s.replace("gnui_check_only_forms", "gnui_check_forms")
   s = s.replace("gnui_set_focus_object", "focus /*TODO:fixme*/")
   s = refactor(s, "gnui_set_object_boxtype", "1->box(2)", 2)
   s = refactor(s, "gnui_set_object_lsize", "1->label_size(2)", 2)
   s = refactor(s, "gnui_set_object_lcol", "1->label_color((GNUI_Color)2)", 2)
   s = refactor(s, "gnui_set_object_lalign", "1->clear_flag(GNUI_ALIGN_MASK);1->set_flag(2)", 2)
   s = refactor(s, "gnui_set_object_color", "1->color((GNUI_Color)2); 1->selection_color((GNUI_Color)3)", 3);
   s = refactor(s, "gnui_set_object_label", "1->label(2); 1->redraw()", 2)
   s = refactor(s, "gnui_set_object_position", "1->position(2,3)", 3)
   s = refactor(s, "gnui_set_object_size", "1->size(2,3)", 3)
   s = refactor(s, "gnui_set_object_geometry", "1->resize(2,3,4,5)", 5)
   s = refactor(s, "gnui_set_object_callback", "1->callback(2,3)", 3)
   s = refactor(s, "gnui_call_object_callback", "1->do_callback()", 1)
   s = refactor(s, "gnui_trigger_object", "1->do_callback()", 1)
   s = refactor(s, "gnui_redraw_object", "1o->redraw()", 1)
   s = refactor(s, "gnui_show_object", "1->show()", 1)
   s = refactor(s, "gnui_hide_object", "1->hide()", 1)
   s = refactor(s, "gnui_free_object", "delete 1;", 1)
   s = refactor(s, "gnui_delete_object", "(GNUI_Group*)(1->parent()))->remove(1))", 1)
   s = refactor(s, "gnui_activate_object", "1->activate()", 1)
   s = refactor(s, "gnui_deactivate_object", "1->deactivate()", 1)
   s = refactor(s, "gnui_add_object", "1->add(2)", 2)
   s = refactor(s, "GNUI_ObjWin", "1->window()", 1)
   s = s.replace("gnui_get_border_width", "3")
   s = noopCode(s, "gnui_set_border_width")
   s = noopCode(s, "gnui_set_object_dblbuffer")
   s = noopCode(s, "gnui_set_form_dblbuffer")
   s = refactor(s, "gnui_free_form", "delete 1" ,1)
   s = refactor(s, "gnui_redraw_form", "1->redraw()", 1)
   s = refactor(s, "gnui_addto_form", "1->begin()", 1)
   s = s.replace("gnui_bgn_group()", "new GNUI_Group(0,0,0,0,0)")
   s = refactor(s, "gnui_addto_group", "((GNUI_Group*)1)->begin()", 1)
   s = refactor(s, "gnui_set_form_position", "1->position(2,3)", 3)
   s = refactor(s, "gnui_set_form_size", "1->size(2,3)", 3)
   s = noopCode(s, "gnui_adjust_form_size")
   s = refactor(s, "gnui_set_form_hotspot", "1->hotspot(2,3)", 3)
   s = refactor(s, "gnui_set_form_hotobject", "1->hotspot(2)", 2)
   s = refactor(s, "gnui_flip_yorigin", "gnui_flip = 1", 0)
   s = noopCode(s, "gnui_show_form_window")
   s = refactor(s, "gnui_raise_form", "1->show()", 1)
   s = refactor(s, "gnui_hide_form", "1->hide()", 1)
   s = refactor(s, "gnui_pop_form", "1->show()", 1)
   s = noopCode(s, "gnui_activate_all_forms")
   s = refactor(s, "gnui_deactivate_all_forms", "gnui_modal_next = 1", 0)
   s = refactor(s, "gnui_deactivate_form", "1->deactivate()", 1)
   s = refactor(s, "gnui_activate_form", "1->activate()", 1)
   s = refactor(s, "gnui_set_form_title", "1->label(2)", 2)
   s = refactor(s, "gnui_title_form", "1->label(2)", 2)
   s = refactor(s, "gnui_set_form_callback", "1->callback(2)", 2)
   s = noopCode(s, "gnui_init");
   s = refactor(s, "gnui_form_is_visible", "1->visible()", 1)
   s = s.replace("gnui_mouse_button", "event_button")
   s = noopCode(s, "gnui_add_new")
   s = refactor(s, "gnui_add_new", "2->type(1); return 2", 2)
   s = refactor(s, "gnui_set_pixmap_align", "1->clear_flag(GNUI_ALIGN_MASK); 1->set_flag(2)", 2)
   s = refactor(s, "gnui_get_button", "((GNUI_Button*)1)->value()", 1)
   s = refactor(s, "gnui_set_button", "((GNUI_Button*)1)->value(2)", 2)
   s = refactor(s, "gnui_get_button_numb", "event_button()", 0)
   s = refactor(s, "gnui_add_bitmapbutton", "gnui_add_button(1,2,3,4,5)", 5)
   s = refactor(s, "gnui_add_pixmapbutton", "gnui_add_button(1,2,3,4,5,6)", 6)
   s = refactor(s, "gnui_set_cursor", "1->cursor(2)", 2)
   s = refactor(s, "gnui_show_question", "gnui_ask(1)", 1)
   s = refactor(s, "gnui_show_question", "gnui_ask(1)", 2)   
   s = refactor(s, "gnui_show_input", "gnui_input(1,2)", 1)
   s = refactor(s, "gnui_show_input", "gnui_input(1,2)", 2)   
   s = refactor(s, "do_matching", "filename_match(1,2)", 2)
   s = refactor(s, "gnui_get_input", "((GNUI_Input*)1)->value()", 1)
   s = refactor(s, "gnui_set_timer", "((GNUI_Timer*)1)->value(2)", 2)
   s = refactor(s, "gnui_get_timer", "((GNUI_Timer*)1)->value()", 1)
   s = refactor(s, "gnui_suspend_timer", "((GNUI_Timer*)1)->suspended(_ONE_)", 1)
   s = refactor(s, "gnui_resume_timer", "((GNUI_Timer*)1)->suspended(1)", 1)
   s = refactor(s, "gnui_set_timer_countup", "((GNUI_Timer*)1)->direction(2))", 2)
   s = s.replace("gnui_double_click()", "event_clicks()")
   s = s.replace("gnui_draw", "flush()")
   s = s.replace("gl_height()", "fltk::glgetascent()+fltk::glgetdescent()")
   return s

def processKeyboard(s):
   # update keyboard constants
   s = s.replace("GNUI_BackSpace", "BackSpaceKey")
   s = s.replace("GNUI_Tab", "TabKey")
   s = s.replace("GNUI_Enter", "ReturnKey")
   s = s.replace("GNUI_Pause", "PauseKey")
   s = s.replace("GNUI_Scroll_Lock", "ScrollLockKey")
   s = s.replace("GNUI_Escape", "EscapeKey")
   s = s.replace("GNUI_Home", "HomeKey")
   s = s.replace("GNUI_Left", "LeftKey")
   s = s.replace("GNUI_Up", "UpKey")
   s = s.replace("GNUI_Right", "RightKey")
   s = s.replace("GNUI_Down", "DownKey")
   s = s.replace("GNUI_Page_Up", "PageUpKey")
   s = s.replace("GNUI_Page_Down", "PageDownKey")
   s = s.replace("GNUI_End", "EndKey")
   s = s.replace("GNUI_Print", "PrintKey")
   s = s.replace("GNUI_Insert", "InsertKey")
   s = s.replace("GNUI_Menu", "MenuKey")
   s = s.replace("GNUI_Help", "HelpKey")
   s = s.replace("GNUI_Num_Lock", "NumLockKey")
   s = s.replace("GNUI_KP_Enter", "KeypadEnter")
   s = s.replace("GNUI_KP_Last", "KeypadLast")
   s = s.replace("GNUI_KP", "Keypad")
   s = s.replace("GNUI_Shift_L", "LeftShiftKey")
   s = s.replace("GNUI_Shift_R", "RightShiftKey")
   s = s.replace("GNUI_Control_L", "LeftCtrlKey")
   s = s.replace("GNUI_Control_R", "RightCtrlKey")
   s = s.replace("GNUI_Caps_Lock", "CapsLockKey")
   s = s.replace("GNUI_Meta_L", "LeftMetaKey")
   s = s.replace("GNUI_Meta_R", "RightMetaKey")
   s = s.replace("GNUI_Alt_L", "LeftAltKey")
   s = s.replace("GNUI_Alt_R", "RightAltKey")
   s = s.replace("GNUI_Delete", "DeleteKey")
   return s

def processEnumerations(s):
   # process enums from Enumerations.H
   s = s.replace("GNUI_KEYDOWN", "KEY")
   s = s.replace("GNUI_KEYBOARD", "KEY")
   # replace colors
   s = s.replace("GNUI_GRAY0", "GRAY00")
   s = s.replace("GNUI_DARK3", "GRAY33")
   s = s.replace("GNUI_DARK2", "GRAY60")
   s = s.replace("GNUI_DARK1", "GRAY66")
   s = s.replace("GNUI_GRAY", "GRAY75")
   s = s.replace("GNUI_BACKGROUND_COLOR", "GRAY75")
   s = s.replace("GNUI_LIGHT1", "GRAY85")
   s = s.replace("GNUI_LIGHT2", "GRAY90")
   s = s.replace("GNUI_LIGHT3", "GRAY99")
   s = s.replace("GNUI_DARK_RED", "fltk::color(128,0,0)")
   s = s.replace("GNUI_DARK_GREEN", "fltk::color(0,128,0)")
   s = s.replace("GNUI_DARK_YELLOW", "fltk::color(128,128,0)")
   s = s.replace("GNUI_DARK_BLUE", "fltk::color(0,0,128)")
   s = s.replace("GNUI_DARK_MAGENTA", "fltk::color(128,0,128)")
   s = s.replace("GNUI_DARK_CYAN", "fltk::color(0,128,128)")
   s = s.replace("GNUI_GRAY_RAMP", "GRAY00")
   s = s.replace("GNUI_COLOR_CUBE", "BLACK")
   # replace Flags.h
   s = s.replace("GNUI_ALIGN_TEXT_OVER_IMAGE", "ALIGN_BOTTOM|ALIGN_INSIDE")
   s = s.replace("GNUI_ALIGN_TOP_LEFT", "ALIGN_TOP|ALIGN_LEFT")
   s = s.replace("GNUI_ALIGN_TOP_RIGHT", "ALIGN_TOP|ALIGN_RIGHT")
   s = s.replace("GNUI_ALIGN_BOTTOM_LEFT", "ALIGN_BOTTOM|ALIGN_LEFT")
   s = s.replace("GNUI_ALIGN_BOTTOM_RIGHT", "ALIGN_BOTTOM|ALIGN_RIGHT")
   s = s.replace("GNUI_ALIGN_LEFT_TOP", "ALIGN_LEFT|ALIGN_TOP")
   s = s.replace("GNUI_ALIGN_RIGHT_TOP", "ALIGN_RIGHT|ALIGN_TOP")
   s = s.replace("GNUI_ALIGN_LEFT_BOTTOM", "ALIGN_LEFT|ALIGN_BOTTOM")
   s = s.replace("GNUI_ALIGN_RIGHT_BOTTOM", "ALIGN_RIGHT|ALIGN_BOTTOM")
   # replace Browser.h
   s = s.replace("GNUI_NORMAL_BROWSER", "Browser::NORMAL")
   s = s.replace("GNUI_SELECT_BROWSER", "Browser::NORMAL")
   s = s.replace("GNUI_HOLD_BROWSER", "Browser::NORMAL")
   s = s.replace("GNUI_MULTI_BROWSER", "Browser::MULTI")
   s = s.replace("GNUI_MULTI_BROWSER", "Browser::MULTI")  
   s = s.replace("GNUI_NORMAL_BUTTON", "Button::NORMAL")
   s = s.replace("GNUI_TOGGLE_BUTTON", "Button::TOGGLE")
   s = s.replace("GNUI_RADIO_BUTTON", "Button::RADIO")
   s = s.replace("GNUI_HIDDEN_BUTTON", "Button::HIDDEN")
   s = s.replace("GNUI_SQUARE_CLOCK", "Clock::SQUARE")
   s = s.replace("GNUI_ROUND_CLOCK", "Clock::ROUND")
   s = s.replace("GNUI_ANALOG_CLOCK", "Clock::SQUARE")
   s = s.replace("GNUI_DIGITAL_CLOCK", "Clock::DIGITAL")
   s = s.replace("GNUI_NORMAL_DIAL", "Dial::NORMAL")
   s = s.replace("GNUI_LINE_DIAL", "Dial::LINE")
   s = s.replace("GNUI_FILL_DIAL", "Dial::FILL")
   s = s.replace("GNUI_NORMAL_INPUT", "Input::NORMAL")
   s = s.replace("GNUI_MULTILINE_INPUT", "Input::MULTILINE")
   s = s.replace("GNUI_SECRET_INPUT", "Input::SECRET")
   s = s.replace("GNUI_INPUT_WRAP", "Input::WORDWRAP")
   s = s.replace("GNUI_MULTILINE_INPUT_WRAP", "Input::WORDWRAP")
   s = s.replace("GNUI_NORMAL_OUTPUT", "Input::NORMAL")
   s = s.replace("GNUI_MULTILINE_OUTPUT", "Input::MULTILINE")
   s = s.replace("GNUI_MULTILINE_OUTPUT_WRAP", "Input::WORDWRAP")
   s = s.replace("GNUI_VERT_SLIDER", "Slider::LINEAR")
   s = s.replace("GNUI_HOR_SLIDER", "Slider::HORIZONTAL")
   s = s.replace("GNUI_VERT_FILL_SLIDER", "Slider::FILL")
   s = s.replace("GNUI_HOR_FILL_SLIDER", "Slider::HORIZONTAL+fltk::Slider::FILL")
   s = s.replace("GNUI_VERT_NICE_SLIDER", "Slider::LINEAR")
   s = s.replace("GNUI_HOR_NICE_SLIDER", "Slider::HORIZONTAL")
   s = s.replace("GNUI_RESERVED_TYPE", "Widget::RESERVED_TYPE")
   return s

def processNamespace(s):
   # replace fltk names
   s = s.replace("FL/GNUI_Menu_Button", "fltk/PopupMenu")
   s = s.replace("FL/GNUI_Double_Window", "fltk/Window")
   s = s.replace("GNUI_Menu_Button", "PopupMenu")
   s = s.replace("GNUI_Double_Window", "Window")
   s = s.replace("FL/gnui_show_input.H", "fltk/ask.h")
   s = s.replace("FL/gnui_message.H", "fltk/ask.h")
   s = s.replace("EXPORT", "GNUI_API")
   s = s.replace("damage(D", "set_damage(D")
   s = s.replace("HORIZONTAL", "ScrollGroup::HORIZONTAL")
   s = s.replace("Boxtype", "Box*")
   
   # convert eg. GNUI_Check_Button to Check_Button but not Key_Func
   s = re.sub("([^\"])GNUI_([\w]*)([a-z])_([A-Z])", "\g<1>\g<2>\g<3>\g<4>", s)

   # specific exceptions to the above rule
   s = s.replace("Style_Table_Entry", "StyleTableEntry")
   
   # close inserted Rectangle's
   # (?s) causes . to also match newlines
   s = re.sub("(?s)(Rectangle\(.*?\));", "\g<1>);", s, 0)

   # mangle #include lines
   s = re.sub("# *include *<FL/Fl.H>", GNUI_INCLUDE, s)
   s = re.sub("# *include *<FL/GNUI_Scrollbar.H>", SCROLL_INCLUDE, s)
   s = re.sub("# *include *<FL/GNUI_", "#include <fltk/", s)
   s = re.sub("# *include *<FL/", "#include <fltk/", s)

   # cleanup bad conversions
   s = s.replace("fltk/drawtext", "fltk/draw")
   
   # (?m) causes ^ and $ to be match \n within a single string
   s = re.sub("(?m)^# *", "#", s)
   s = s.replace(".H", ".h")
   s = s.replace("Fl::", "fltk::")
   s = s.replace("<FL/", "<fltk/")
   s = s.replace("#include <fltk/Preferences.h>", "")

   # remove Fl prefixes that don't begin with double-quote
   # to prevent renaming user include files with this prefix
   s = re.sub("([^\"])gnui_", "\g<1>", s)
   s = re.sub("([^\"])GNUI_", "\g<1>", s)
   s = re.sub("([^\"])GNUI_", "\g<1>", s)

   return s

def processHeader(s):
   # insert using namespace fltk into all headers
   i = s.rfind("#include")
   if (i != -1):
      i = s.find("\n", i)
      s = s[:i]+"\n\nusing namespace fltk;"+s[i:]
   
   return s

def process(fileName):
   if (os.access(backupDir+"/"+fileName, os.R_OK) == 0):
      shutil.copyfile(fileName, backupDir+"/"+fileName)

   f = open(fileName, 'rw')
   s = f.read()

   # check if the file has already been processed
   if (s.endswith(codeComment)):
      return

   print fileName

   s = processHashDefines(s)
   s = processInlines(s)
   s = processKeyboard(s)   
   s = processEnumerations(s)
   s = processNamespace(s)

   if (fileName.endswith(".h") or
       fileName.endswith(".H")):
       s = processHeader(s)
  
   f.close()
   f = open(fileName, 'w')
   f.write(s)
   f.write(codeComment)
   f.close()   
   
def main():
   # create the backup directory if it doesn't already exist
   if (os.access(backupDir, os.R_OK|os.W_OK) == 0):
      os.mkdir(backupDir)
      
   if (len(sys.argv) == 1):
      # process all source files in current directory
      files = glob.glob("*.h")
      files.extend(glob.glob("*.H"))
      files.extend(glob.glob("*.cxx"))
      files.extend(glob.glob("*.cpp"))
      for i in range(len(files)):
         process(files[i])
   else:
      # process all source files specified on the command line
      for i in range(1, len(sys.argv)):
         process(sys.argv[i])

main()

#
# ChangeLog
#
# 0.2 - 
# * Only remove userscores from GNUI_xx_Xxx variables (not user variables)
# * Insert "using namespace fltk" after the pattern #ifndef xxx\n#define xxx\n
#   and only in header files. (In lieu of before the word 'class'
# * renamed "delete unused imports" to "delete unused header files"
# * fixed problem with refactor() skipping lines
# * handle more conversions found in FL/gnui_draw.H
# * processHashDefines() is now invoked
# * conversions for GNUI_DARK_xxx colours
#
# 0.1 - October 2005
# * Initial version
#
# End of $Id: $"

